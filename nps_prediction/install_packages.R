user_lib <- "C:/Users/migue/OneDrive/Bureau/info/python/data_engineering/nps_prediction/packages"

if (!dir.exists(user_lib)) dir.create(user_lib, recursive = TRUE)

packages <- c(
  "tidyverse",
  "randomForest",
  "caret",
  "tm",
  "wordcloud",
  "tidytext",
  "shiny",
  "lubridate",
  "glue"
)

install_if_missing <- function(pkg){
  if (!requireNamespace(pkg, quietly = TRUE)) {
    install.packages(pkg, repos = "https://cloud.r-project.org", lib = user_lib)
  }
}

invisible(sapply(packages, install_if_missing))

cat("✅ Packages installés dans :", user_lib, "\n")