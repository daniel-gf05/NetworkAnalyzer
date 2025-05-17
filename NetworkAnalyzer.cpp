#include "NetworkAnalyzer.h"
#include <iostream>
#include <pcap.h>

// Dispositivo
char source[30];
pcap_t* handle;

// Inicio el capturador de paquetes (pcap)
int initPcap()
{

    // Buffer que captura un posible error
    char errbuf[PCAP_ERRBUF_SIZE];

    if (pcap_init(PCAP_CHAR_ENC_UTF_8, errbuf) != 0)
    {
        std::cout << "Error al iniciar el capturador de paquetes" << "\n";
        return -1;
    }

    std::cout << "Capturador de paquetes iniciado..." << "\n";

    return 0;
}

char *askSource()
{
    // Aquí debería listar las interfaces TO-DO
    std::cout << "Introduce la interfaz de red para la captura: ";
    std::cin >> source;
    // Aquí debería comprobar si la interfaz existe TO-DO
    return source;
}

// Creo un handle para manejar la captura de paquetes
int createPcap()
{
    char errbuf[PCAP_ERRBUF_SIZE];
    askSource();
    handle = pcap_create(source, errbuf);
    if (handle == NULL)
    {
        std::cout << "Error al crear el HANDLE, compruebe el dispositivo" << "\n";
        return -1;
    }

    std::cout << "Handle creado..." << "\n";

    return 0;
}

// Activar el handle creado anteriormente
int activateHandle(){
    if (pcap_activate(handle) < 0)
    {
        std::cout << "Error al activar el handle\n";
        return -1;
    }
    if (pcap_activate(handle) > 0)
    {
        std::cout << "Se ha activado el handle con avisos\n";
        return -1;
    }

    std::cout << "El handle ha sido activado...";

    return 0;
    
}

int program()
{
    initPcap();
    createPcap();
    activateHandle();
    return 0;
}