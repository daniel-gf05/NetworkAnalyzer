#include "NetworkAnalyzer.h"
#include <iostream>
#include <pcap.h>


int initPcap(){
    
    char errbuf[PCAP_ERRBUF_SIZE];

    if (pcap_init(PCAP_CHAR_ENC_UTF_8, errbuf) != 0)
    {
        std::cout << "Error al iniciar el capturador de paquetes" << "\n";
    }

    std::cout << "Capturador de paquetes iniciado..." << "\n";
    
    return 0;
}