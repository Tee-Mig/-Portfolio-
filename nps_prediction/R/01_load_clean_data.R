# Indiquer à R de chercher les packages dans le dossier local "packages"
.libPaths(c(normalizePath("packages"), .libPaths()))

# Charger les packages nécessaires
library(readr)
library(dplyr)
library(lubridate)
library(glue)  # nécessaire pour glue::glue()

local_lib <- "packages"

# Chargement des données
df <- read_csv("data/feedback_clients.csv")

# Infos sur le dataset
print(glue::glue("Dataset : {nrow(df)} lignes, {ncol(df)} colonnes"))

# Comptage des valeurs manquantes
missing_summary <- sapply(df, function(x) sum(is.na(x)))
print("Valeurs manquantes par colonne :")
print(missing_summary)

# Suppression des doublons
df <- df %>% distinct()

# Structure du dataframe
str(df)

# Conversion des types
df <- df %>%
  mutate(
    date = as.Date(date),
    produit_endommage = as.factor(produit_endommage),
    retard = as.factor(retard)
  )

# Création de la variable catégorielle NPS
df <- df %>%
  mutate(
    nps_class = case_when(
      note_NPS >= 9 ~ "promoteur",
      note_NPS >= 7 ~ "passif",
      TRUE ~ "detracteur"
    ),
    nps_class = factor(nps_class, levels = c("detracteur", "passif", "promoteur"))
  )

# Résumé statistique
summary(df)

# Sauvegarde des données nettoyées
saveRDS(df, file = "data/df_cleaned.rds")
write_csv(df, file = "data/df_cleaned.csv")

cat("✅ Données nettoyées et sauvegardées.\n")
