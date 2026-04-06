# 🚀 Batalha dos Drones (C)

Projeto desenvolvido no âmbito da unidade curricular de **Introdução à Programação**.

Inspirado no clássico jogo *Batalha Naval*, este programa simula uma **Batalha dos Drones**, onde o objetivo é identificar e eliminar peças de artilharia inimigas num mapa desconhecido.

---

## 🎯 Objetivo

Reconhecer e destruir todas as peças de artilharia utilizando drones, com base em informação parcial obtida ao longo da execução.

De acordo com o enunciado, cada peça:
- Está numa posição desconhecida
- Afeta a sua própria célula e as **8 células vizinhas**
- Necessita de **3 drones na posição exata** para ser destruída :contentReference[oaicite:0]{index=0}

---

## 🧠 Conceitos Aplicados

- Matrizes bidimensionais
- Geração pseudoaleatória
- Simulação de estados (desconhecido / seguro / inseguro)
- Processamento de input do utilizador
- Lógica condicional e iterativa

---

## 🗺️ Funcionalidades

### 🔹 1. Geração do Mapa
- Criação de um mapa NxN (até 10x10)
- Distribuição aleatória de peças de artilharia com base numa probabilidade (1 em N)
- Visualização do mapa com:
  - `.` → vazio  
  - `#` → artilharia  

---

### 🔹 2. Lançamento de Drones
- Introdução de coordenadas (ex: `A2`, `C3`)
- Cada drone pode:
  - **Sobreviver** → zona segura (`.`)
  - **Ser abatido** → zona insegura (`!`)
- Estados possíveis do mapa:
  - `?` → desconhecido  
  - `.` → seguro  
  - `!` → inseguro  

---

### 🔹 3. Campanha
- Simulação por dias (máx. 10)
- Gestão de drones:
  - Número limitado de drones
  - Drones abatidos não podem ser reutilizados
  - Recebe 1 novo drone por dia
- Condição de vitória:
  - Todas as células seguras

---


## 🧪 Exemplo de Execução
<img width="1103" height="1162" alt="image" src="https://github.com/user-attachments/assets/d874ece7-eade-4234-b2fb-1490e144cefd" />
