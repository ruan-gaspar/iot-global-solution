# Projeto Monitoramento de Insalubridade com IoT

## Integrantes
- Ruan Nunes Gaspar RM 559567 Turma 2TDSPA  
- Rodrigo Paes Morales RM 560209 Turma 2TDSPA  
- Fernando Nachtigall Tessmann RM 559617 Turma 2TDSPR  

## Objetivo do projeto
Criar uma solução para empresas monitorarem seus níveis de insalubridade em linhas de produção ou outros setores, através da integração de sensores IoT. O sistema utiliza sensores de temperatura, umidade, monóxido de carbono (CO), dióxido de carbono (CO2), gás metano (CH4) e gás sulfídrico (H2S), por exemplo, um gás perigoso comum em ambientes industriais. Os dados coletados pelos sensores são transmitidos para uma aplicação .NET MVC que apresenta um dashboard para visualização em tempo real.

---

## Introdução
Este projeto une tecnologias de IoT, processamento de dados e visualização para auxiliar empresas a monitorar ambientes potencialmente insalubres. O fluxo de dados inicia com sensores simulados via Wokwi e sensores físicos, que enviam informações via MQTT para o Node-RED. O Node-RED processa essas mensagens, exibe dados em dashboard interno e repassa os dados para uma API .NET que faz o tratamento, processamento e apresentação para usuários finais.

---

## Como usar

### Pré-requisitos
- Conta gratuita no [Adafruit IO](https://io.adafruit.com/) para receber dados via MQTT (crie a conta, configure feeds para sensores).
- Instalar [Node-RED](https://nodered.org/) (disponível para Linux e Windows).
- Instalar [ngrok](https://ngrok.com/) para expor localmente a API e Node-RED para internet.
- Ter o [Postman](https://www.postman.com/) para testes API HTTP.
- .NET SDK e ambiente para rodar a API .NET MVC.
- (Opcional) Familiaridade com [Wokwi](https://wokwi.com/) para simulação dos sensores.

---

### Instalação e Configuração

#### Node-RED

1. Instale o Node.js (requerido pelo Node-RED):
   - Linux (Debian/Ubuntu):  
     ```
     sudo apt update
     sudo apt install nodejs npm
     ```
   - Windows: Baixe e instale [Node.js](https://nodejs.org/).

2. Instale o Node-RED globalmente:  
npm install -g --unsafe-perm node-red


3. Inicie o Node-RED:  
node-red


4. Importe o arquivo `flows.json` (presente no repositório) pelo editor Web do Node-RED (`http://localhost:1880`).

#### ngrok

1. Crie conta gratuita no [ngrok](https://ngrok.com/) e configure o token de autenticação conforme instruções do site.

2. Baixe e instale ngrok para seu sistema operacional.

3. Exponha a porta local 1880 (Node-RED) ou a porta da sua API .NET, por exemplo:  
ngrok http 1880

4. Copie a URL pública HTTPS gerada (ex: `https://abcdefg123.ngrok-free.dev`).

5. Use essa URL para acessar remotamente a dashboard do Node-RED e para configurar o http request no fluxo que envia dados para a API .NET.

#### API .NET MVC

1. Clone o repositório e configure seu ambiente .NET conforme seu sistema operacional (Windows ou Linux).

2. Atualize a API para usar a URL pública do ngrok que expõe o Node-RED ou vice-versa, no endpoint para receber dados.

---

### Usando o Adafruit IO

- Crie feeds para sensores (temperatura, umidade, CO, CO2, CH4, H2S).
- Configure seu dispositivo IoT (simulado via Wokwi ou dispositivo real) para publicar nos feeds MQTT do Adafruit IO.
- Configure o Node-RED para conectar-se ao broker MQTT do Adafruit IO com sua chave e receber mensagens dos feeds.

---

### Sobre Wokwi

O Wokwi é um simulador online de dispositivos IoT (Arduino, ESP32), usado para criar protótipos virtuais de sensores. No projeto, os sensores virtuais enviam dados para Adafruit IO e são recebidos pelo Node-RED.

---

## Testes

### Testando o fluxo MQTT → Node-RED

- Confirme recepção de dados no debug do Node-RED e nos gauges do painel.

### Testando envio para API .NET via ngrok

- No Postman configure uma requisição POST para a URL pública do ngrok + `/api/sensores`.  
- Envie JSON com exemplo:  
{
"temperatura": 26.5,
"umidade": 70.3,
"monoxidoCarbono": 0.3,
"dioxidoCarbono": 0.8,
"gasMetano": 0.05,
"gasSulfidrico": 0.01
}

- Verifique resposta da API e status HTTP.

### Testando recebimento via API .NET

- Use browser ou Postman para consultar endpoint que retorna dados salvos/armazenados, via GET.

---

## Conclusão

Este projeto demonstra uma aplicação prática da Internet das Coisas integrada a sistemas web para controle ambiental industrial. Usamos sensores reais e simulados para monitoramento, Node-RED para processamento com interface visual, ngrok para exposição segura da aplicação, e uma API .NET MVC para back-end. A solução é extensível e pode ser adaptada para variados usos em monitoramento de saúde e segurança no trabalho.

---

## Repositório

- Todo o código Node-RED está no arquivo `flows.json` disponível no repositório.
- API .NET com endpoints para recepção e consulta dos sensores também encontra-se no repositório.

