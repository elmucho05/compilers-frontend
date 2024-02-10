
#### Esercizio 6.1
The built-in data set iris is a data frame containing measurements of the sepals and petals of 150 iris flowers. Convert this data to a tibble with new variables  `Sepal.Area` and `Petal.Area` which are the product of the corresponding length and width measurements.  
```R
data(iris)

# Crea il tibble con nuove variabili Sepal.Area e Petal.Area

iris_tibble <- iris %>%

  mutate(Sepal.Area = Sepal.Length * Sepal.Width,

         Petal.Area = Petal.Length * Petal.Width) %>%

  as_tibble()

# Visualizza le prime righe del nuovo tibble

head(iris_tibble)

```


### # Installa il pacchetto tidyverse 

# install.packages("tidyverse")

# Carica il pacchetto tidyverse

library(tidyverse)

# Carica il data set iris
