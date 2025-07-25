# Définir le chemin local pour les packages
.libPaths(c(normalizePath("packages"), .libPaths()))

# Chargement des librairies
library(stringr)
library(dplyr)
library(tidytext)
library(tm)
library(wordcloud)
library(ggplot2)
library(glue)

# Charger les données nettoyées
df <- readRDS("data/df_cleaned.rds")

cat(glue("Commentaires à analyser : {sum(!is.na(df$commentaire))} / {nrow(df)} lignes\n"))

# Nettoyage de base des commentaires
df_clean_text <- df %>%
  filter(!is.na(commentaire) & commentaire != "") %>%
  mutate(commentaire = tolower(commentaire))  # passage en minuscules

# Tokenisation (1 mot par ligne)
tokens <- df_clean_text %>%
  select(nps_class, commentaire) %>%
  unnest_tokens(word, commentaire)

# Suppression des mots vides (stopwords)
data("stop_words")  # liste intégrée dans tidytext
tokens_clean <- tokens %>%
  anti_join(stop_words, by = "word") %>%
  filter(!str_detect(word, "^[0-9]+$"))  # supprimer les nombres

# Top 15 des mots les plus fréquents
top_words <- tokens_clean %>%
  count(word, sort = TRUE) %>%
  slice_max(n, n = 15)

print("🔤 Mots les plus fréquents (top 15) :")
print(top_words)

# Visualisation en barplot
ggplot(top_words, aes(x = reorder(word, n), y = n)) +
  geom_col(fill = "#0073C2") +
  coord_flip() +
  labs(title = "Top 15 des mots les plus fréquents dans les commentaires",
       x = "Mot", y = "Nombre d'occurrences") +
  theme_minimal()

# Nuage de mots global
word_freq <- tokens_clean %>%
  count(word) %>%
  filter(n > 2)

set.seed(123)
wordcloud(words = word_freq$word,
          freq = word_freq$n,
          min.freq = 3,
          colors = brewer.pal(8, "Dark2"),
          max.words = 100)

# Comparaison des mots par classe NPS
words_by_class <- tokens_clean %>%
  count(nps_class, word) %>%
  group_by(nps_class) %>%
  slice_max(n, n = 10)

print("🔠 Mots caractéristiques par classe NPS :")
print(words_by_class)

# Nuages de mots par classe NPS
par(mfrow = c(1, 3))  # 3 nuages côte à côte
for (class in unique(words_by_class$nps_class)) {
  subset_words <- filter(words_by_class, nps_class == class)
  wordcloud(words = subset_words$word,
            freq = subset_words$n,
            min.freq = 1,
            max.words = 50,
            scale = c(2.5, 0.7),
            colors = brewer.pal(8, "Dark2"))
  title(main = paste("Classe :", class))
}
par(mfrow = c(1,1))

cat("✅ Analyse textuelle terminée.\n")
