# .libPaths("C:/Users/migue/OneDrive/Bureau/info/python/data_engineering/nps_prediction/packages")
.libPaths(c(normalizePath("packages"), .libPaths()))

library(shiny)
library(ggplot2)
library(dplyr)
library(readr)
library(glue)

df <- readRDS("data/df_cleaned.rds")
rf_model <- readRDS("models/rf_model.rds")

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

server <- function(input, output) {
  output$plot_nps <- renderPlot({
    df %>%
      count(nps_class) %>%
      ggplot(aes(x = nps_class, y = n, fill = nps_class)) +
      geom_col() +
      theme_minimal() +
      labs(title = "Répartition des classes NPS", x = "Classe", y = "Nombre de clients") +
      theme(legend.position = "none")
  })

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

  observeEvent(input$predire, {
    new_obs <- data.frame(
      montant_commande = input$montant,
      temps_livraison = input$livraison,
      retard = factor(input$retard, levels = levels(df$retard)),
      produit_endommage = factor(input$endommage, levels = levels(df$produit_endommage))
    )

    pred <- predict(rf_model, newdata = new_obs)
    output$prediction_result <- renderText({
      glue::glue("Classe prédite : {pred}")
    })
  })
}

shinyApp(ui = ui, server = server)
