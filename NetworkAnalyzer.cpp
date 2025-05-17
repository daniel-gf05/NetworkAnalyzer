#include "NetworkAnalyzer.h"
#include <iostream>
#include <pcap.h>
#include <unistd.h>

// Dispositivo
char source[30];
pcap_t *handle;

// Compruebo que el programa haya sido ejecutado con privilegios
int checkRoot()
{
    if (geteuid() != 0)
    {
        std::cout << "El programa debe de ejecutarse como root/administrador" << "\n";
        return -1;
    }
    return 0;
}

// Inicio el capturador de paquetes (pcap)
int initPcap()
{

    // Buffer que captura un posible error
    char errbuf[PCAP_ERRBUF_SIZE];

    if (pcap_init(PCAP_CHAR_ENC_UTF_8, errbuf) != 0)
    {
        std::cout << "Error al iniciar el capturador de paquetes. Error: " << errbuf << "\n";
        return -1;
    }

    std::cout << "Capturador de paquetes iniciado..." << "\n";

    return 0;
}

// Líneas copiadas de CHATGPT, repasar
int listDevices()
{
    pcap_if_t *alldevs;
    char errbuf[PCAP_ERRBUF_SIZE];

    if (pcap_findalldevs(&alldevs, errbuf) == -1)
    {
        std::cerr << "Error: " << errbuf << std::endl;
        return 1;
    }

    // Ahora 'alldevs' apunta a la lista de interfaces disponibles
    for (pcap_if_t *d = alldevs; d != nullptr; d = d->next)
    {
        std::cout << "Interface: " << d->name << std::endl;
    }

    pcap_freealldevs(alldevs); // Liberar memoria
    return 0;
}

char *askSource()
{
    char errbuf[PCAP_ERRBUF_SIZE];
    listDevices();
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
        std::cout << "Error: " << errbuf << "\n";
        return -1;
    }

    std::cout << "Handle creado..." << "\n";

    return 0;
}

// Activar el handle creado anteriormente
int activateHandle()
{
    if (pcap_activate(handle) < 0)
    {
        std::cout << "Error al activar el handle" << "\n";
        pcap_close(handle);
        return -1;
    }
    if (pcap_activate(handle) > 0)
    {
        std::cout << "Se ha activado el handle con avisos\n";
        return -1;
    }

    std::cout << "El handle ha sido activado...\n";

    return 0;
}

int program()
{
    if (checkRoot() != 0){return -1;}
    initPcap();
    createPcap();
    activateHandle();
    return 0;
}