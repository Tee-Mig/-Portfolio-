# .libPaths("C:/Users/migue/OneDrive/Bureau/info/python/data_engineering/nps_prediction/packages")
.libPaths(c(normalizePath("packages"), .libPaths()))

# Chargement des bibliothèques
library(shiny)
library(ggplot2)
library(dplyr)
library(readr)

# Charger les données nettoyées
df <- readRDS("data/df_cleaned.rds")
rf_model <- readRDS("models/rf_model.rds")

# Interface utilisateur (UI)
ui <- fluidPage(
  titlePanel("📊 Dashboard NPS - Carrefour Feedback"),

  sidebarLayout(
    sidebarPanel(
      h4("🎯 Prédiction de la classe NPS"),
      numericInput("montant", "Montant commande (€)", value = 50, min = 0),
      numericInput("livraison", "Temps de livraison (jours)", value = 2, min = 0),
      selectInput("retard", "Retard de livraison ?", choices = c("Non" = 0, "Oui" = 1)),
      selectInput("endommage", "Produit endommagé ?", choices = c("Non" = 0, "Oui" = 1)),
      actionButton("predire", "Prédire", class = "btn-primary")
    ),

    mainPanel(
      tabsetPanel(
        tabPanel("Vue d'ensemble",
          plotOutput("plot_nps"),
          plotOutput("plot_montant")
        ),
        tabPanel("Résultat prédiction",
          verbatimTextOutput("prediction_result")
        )
      )
    )
  )
)

# Serveur (Server)
server <- function(input, output) {
  # Graphique : distribution des classes NPS
  output$plot_nps <- renderPlot({
    df %>%
      count(nps_class) %>%
      ggplot(aes(x = nps_class, y = n, fill = nps_class)) +
      geom_col() +
      theme_minimal() +
      labs(title = "Répartition des classes NPS", x = "Classe", y = "Nombre de clients") +
      theme(legend.position = "none")
  })

  # Graphique : montant moyen par classe
  output$plot_montant <- renderPlot({
    df %>%
      group_by(nps_class) %>%
      summarise(montant_moyen = mean(montant_commande)) %>%
      ggplot(aes(x = nps_class, y = montant_moyen, fill = nps_class)) +
      geom_col() +
      theme_minimal() +
      labs(title = "Montant moyen par classe NPS", x = "Classe", y = "Montant moyen (€)") +
      theme(legend.position = "none")
  })

  # Prédiction
  observeEvent(input$predire, {
    # Création d'une nouvelle observation
    new_obs <- data.frame(
      montant_commande = input$montant,
      temps_livraison = input$livraison,
      retard = as.factor(input$retard),
      produit_endommage = as.factor(input$endommage)
    )

    # Prédiction
    pred <- predict(rf_model, newdata = new_obs)
    output$prediction_result <- renderText({
      glue::glue("Classe prédite : {pred}")
    })
  })
}

# Lancer l'application
shinyApp(ui = ui, server = server)
