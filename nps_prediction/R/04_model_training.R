.libPaths(c(normalizePath("packages"), .libPaths()))

library(dplyr)
library(randomForest)
library(caret)
library(glue)

df <- readRDS("data/df_cleaned.rds")
cat(glue("Données chargées : {nrow(df)} lignes\n"))


df_model <- df %>%
  select(nps_class, montant_commande, temps_livraison, retard, produit_endommage) %>%
  filter(!is.na(nps_class)) %>%
  mutate(
    nps_class = as.factor(nps_class),
    retard = as.factor(retard),
    produit_endommage = as.factor(produit_endommage)
  )

set.seed(42)
train_index <- createDataPartition(df_model$nps_class, p = 0.8, list = FALSE)
train_data <- df_model[train_index, ]
test_data <- df_model[-train_index, ]

cat(glue("Entraînement : {nrow(train_data)} lignes / Test : {nrow(test_data)} lignes\n"))

rf_model <- randomForest(nps_class ~ ., data = train_data, ntree = 100, importance = TRUE)

cat("✅ Modèle entraîné avec randomForest\n\n")

predictions <- predict(rf_model, test_data)

conf_mat <- confusionMatrix(predictions, test_data$nps_class)

print(conf_mat)

importance_df <- as.data.frame(importance(rf_model))
importance_df$variable <- rownames(importance_df)
importance_df <- importance_df %>% arrange(desc(MeanDecreaseGini))

cat("\n📊 Variables les plus importantes :\n")
print(importance_df[, c("variable", "MeanDecreaseGini")])

saveRDS(rf_model, file = "models/rf_model.rds")

cat("\n✅ Modèle sauvegardé dans models/rf_model.rds\n")
