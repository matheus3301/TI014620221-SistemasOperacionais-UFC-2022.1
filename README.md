# TI014620221-SistemasOperacionais-UFC-2022.1

## Arquivos especiais
Os arquivos especiais são um tipo de arquivo do sistema operacional linux
que expõe dispositivos como arquivos no sistema de arquivos. Os arquivos
especiais podem ser do tipo bloco ou caractere.

- Arquivos bloco
Representam dispositivos que são lidos e escritos em blocos.

- Arquivos caractere
Representam dispositivos que são lidos e escritos em caracteres, ou seja,
em 8 bytes.

## Arquivo caractere do teclado
O teclado, assim como outros dispositivos E/S, possui um arquivo especial
no sistema de arquivos que o representa. Ele estará na pasta /dev/input e
terá o nome event*, sendo * um número que pode variar de acordo com os
dispositivos que estão conectados no computador. Dessa forma, para identificarmos
qual dos arquivos é o correspondente ao teclado vamos acessar a pasta
/proc/bus/input. A pasta proc guarda informações do sistema em tempo de execução,
podendo ser interpretada como um registro do estado do sistema. Em /proc/bus/input
há um arquivo chamado devices que guarda informações sobre todos os dispositivos
do sistema, entre eles o teclado. Para identificarmos qual dos dispositivos listados
é o teclado, basta olhar para o campo EV, que guarda uma bitmask das operações que
o dispositivo suporta. Teclados geralmente possuem o valor EV=120013. Dado que o
dispositivo com essa bitmask foi encontrando, basta buscar nos seus handlers qual
o seu arquivo de event.
