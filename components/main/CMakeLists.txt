# Fügt main.c zum app-Target hinzu und linkt die Komponenten.
target_sources(app PRIVATE src/main.c)
target_link_libraries(app PRIVATE component_a component_b)
