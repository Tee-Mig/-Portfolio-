.libPaths(c(normalizePath("packages"), .libPaths()))

library(readr)
library(dplyr)
library(ggplot2)
library(lubridate)
library(glue)

df <- readRDS("data/df_cleaned.rds")

cat(glue("Dataset chargé : {nrow(df)} lignes\n\n"))

ggplot(df, aes(x = note_NPS)) +
  geom_histogram(binwidth = 1, fill = "#0073C2FF", color = "white") +
  labs(title = "Distribution des scores NPS",
       x = "Score NPS", y = "Nombre de clients") +
  theme_minimal()

df %>%
  count(nps_class) %>%
  mutate(freq = n / sum(n)) %>%
  ggplot(aes(x = nps_class, y = freq, fill = nps_class)) +
  geom_col() +
  scale_y_continuous(labels = scales::percent) +
  labs(title = "Répartition des classes NPS",
       x = "Classe NPS", y = "Pourcentage") +
  theme_minimal() +
  theme(legend.position = "none")

ggplot(df, aes(x = temps_livraison)) +
  geom_histogram(binwidth = 0.5, fill = "#E69F00", color = "white") +
  labs(title = "Distribution du temps de livraison (jours)",
       x = "Temps de livraison (jours)", y = "Nombre de commandes") +
  theme_minimal()

df %>%
  group_by(retard) %>%
  summarise(nps_moyen = mean(note_NPS, na.rm = TRUE)) %>%
  ggplot(aes(x = retard, y = nps_moyen, fill = retard)) +
  geom_col() +
  labs(title = "NPS moyen selon présence de retard",
       x = "Retard (0=non, 1=oui)", y = "NPS moyen") +
  theme_minimal() +
  theme(legend.position = "none")

df %>%
  group_by(nps_class) %>%
  summarise(montant_moyen = mean(montant_commande, na.rm = TRUE)) %>%
  ggplot(aes(x = nps_class, y = montant_moyen, fill = nps_class)) +
  geom_col() +
  labs(title = "Montant moyen des commandes par classe NPS",
       x = "Classe NPS", y = "Montant moyen (€)") +
  theme_minimal() +
  theme(legend.position = "none")

df %>%
  mutate(mois = floor_date(date, "month")) %>%
  group_by(mois) %>%
  summarise(nps_moyen = mean(note_NPS, na.rm = TRUE)) %>%
  ggplot(aes(x = mois, y = nps_moyen)) +
  geom_line(color = "#D55E00") +
  geom_point() +
  labs(title = "Evolution mensuelle du NPS moyen",
       x = "Mois", y = "NPS moyen") +
  theme_minimal()

df %>%
  mutate(nb_mots = sapply(strsplit(commentaire, " "), length)) %>%
  ggplot(aes(x = nps_class, y = nb_mots, fill = nps_class)) +
  geom_boxplot() +
  labs(title = "Distribution du nombre de mots dans les commentaires par classe NPS",
       x = "Classe NPS", y = "Nombre de mots") +
  theme_minimal() +
  theme(legend.position = "none")

cat("✅ EDA terminée.\n")
