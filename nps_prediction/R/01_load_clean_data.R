.libPaths(c(normalizePath("packages"), .libPaths()))

library(readr)
library(dplyr)
library(lubridate)
library(glue)

local_lib <- "packages"

df <- read_csv("data/feedback_clients.csv")

print(glue::glue("Dataset : {nrow(df)} lignes, {ncol(df)} colonnes"))

missing_summary <- sapply(df, function(x) sum(is.na(x)))
print("Valeurs manquantes par colonne :")
print(missing_summary)

df <- df %>% distinct()

str(df)

df <- df %>%
  mutate(
    date = as.Date(date),
    produit_endommage = as.factor(produit_endommage),
    retard = as.factor(retard)
  )

df <- df %>%
  mutate(
    nps_class = case_when(
      note_NPS >= 9 ~ "promoteur",
      note_NPS >= 7 ~ "passif",
      TRUE ~ "detracteur"
    ),
    nps_class = factor(nps_class, levels = c("detracteur", "passif", "promoteur"))
  )

summary(df)

saveRDS(df, file = "data/df_cleaned.rds")
write_csv(df, file = "data/df_cleaned.csv")

cat("✅ Données nettoyées et sauvegardées.\n")
