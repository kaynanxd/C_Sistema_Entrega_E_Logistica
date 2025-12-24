# 🚚 Sistema de Logística e Gestão de Entregas

Este projeto é um sistema de gerenciamento logístico desenvolvido inteiramente na **linguagem C**. O software foi criado como requisito para a disciplina de **Programação e Algoritmos** na **Universidade Estadual do Ceará (UECE)**, aplicando conceitos de estruturas de dados e manipulação de arquivos.

---

## 📋 Sobre o Projeto

O sistema simula a operação de uma empresa de logística, permitindo o controle total sobre o fluxo de mercadorias, veículos e destinos. O foco principal foi a implementação de um **CRUD completo** (Create, Read, Update, Delete) com regras de validação rigorosas.

---

## 🛠️ Funcionalidades e Regras de Negócio

O sistema opera através de diversas condições lógicas para garantir a eficiência da entrega:

* **CRUD de Encomendas:** Cadastro, consulta, edição e remoção de pacotes.
* **Gestão de Frota:** Controle de veículos disponíveis e capacidade de carga.
* **Sistema de Prioridades:** Condições que definem a ordem de entrega com base no tipo de carga ou distância.
* **Cálculo de Frete:** Algoritmos que calculam o custo com base no peso, volume e destino.
* **Status em Tempo Real:** Verificação de condições (ex: "Em processamento", "Em rota", "Entregue").
* **Validação de Dados:** Filtros que impedem cadastros duplicados ou valores de carga negativos.


---

## 💻 Aspectos Técnicos (C Nativo)

Para este projeto acadêmico, foram utilizados conceitos avançados da linguagem C:
* **Structs:** Para modelagem de dados complexos (Caminhões, Clientes e Entregas).
* **Ponteiros:** Manipulação eficiente de dados e passagem de parâmetros.
* **Manipulação de Arquivos:** Persistência de dados em arquivos `.txt` ou `.dat` (binários).
* **Algoritmos de Busca e Ordenação:** Organização de entregas por prazo ou destino.
* **Alocação Dinâmica:** Gerenciamento de memória para listas de pedidos.



