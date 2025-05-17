# Establece la versión mínima de CMake
cmake_minimum_required(VERSION 3.10)

# Define el nombre del proyecto
project(NetworkAnalyzer)

# Define la versión de C++
set(CMAKE_CXX_STANDARD 23)

# Crea el ejecutable especificando los archivos a compilar *REVISAR* LE METO EL HEADER?
# Primero el nombre del ejecutable, después archivos a compilar
# Los headers no se incluyen, ya están enlazados en el .cpp
add_executable(NetworkAnalyzer Main.cpp NetworkAnalyzer.cpp)

# Especifica las librerías/dependencias que voy a usar en mi programa
# Busca la librería "pcap", si la encuentra la almacena en RUTA_PCAP, si no lanza un ERROR gracias al parámetro REQUIRED
find_library(RUTA_PCAP pcap REQUIRED)

# Si ha encontrado la librería, la enlaza con el ejecutable
# Con el parámetro PRIVATE, indico que la biblioteca solo se va a usar en el ejecutable
target_link_libraries(NetworkAnalyzer PRIVATE ${RUTA_PCAP})

# Equivalente en G++
# g++ main.cpp NetworkAnalyzer.cpp -lpcap -o NetworkAnalyzer