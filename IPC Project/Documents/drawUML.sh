#!/bin/bash

# Check if plantuml.jar exists
if [[ ! -f "plantuml.jar" ]]; then
    wget https://github.com/plantuml/plantuml/releases/download/v1.2025.4/plantuml-gplv2-1.2025.4.jar -O ./plantuml.jar
fi

# Run PlantUML
java -jar plantuml.jar diagram.puml
