# Guia de Execução

## Setup Local

### 1. Clonar o Repositório

```bash
git clone git@github.com:SEU_USUARIO/c-game-raylib.git
cd c-game-raylib
```

### 2. Instalar Dependências do Sistema

Exemplo para Ubuntu/Debian:

```bash
sudo apt update
sudo apt install build-essential git cmake
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev
sudo apt install libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev
sudo apt install libxinerama-dev libwayland-dev libxkbcommon-dev
```

### 3. Instalar raylib

Se a distribuição oferecer pacote de desenvolvimento:

```bash
sudo apt install libraylib-dev
```

Se o pacote não estiver disponível, compile a raylib a partir do código-fonte e instale no sistema:

```bash
git clone https://github.com/raysan5/raylib.git
cd raylib
mkdir -p build
cd build
cmake -DBUILD_SHARED_LIBS=ON ..
cmake --build .
sudo cmake --install .
sudo ldconfig
```

### 4. Compilar com CMake

Execute na raiz do projeto:

```bash
cmake -S . -B build
cmake --build build
```

O executável esperado é:

```bash
build/game
```

### 5. Executar o Jogo

Execute a partir do diretório `build/`, porque o código carrega assets com caminhos relativos `../assets/...`:

```bash
cd build
./game
```

---

## Scripts Disponíveis

### CMake

| Comando | Descrição |
| ------- | --------- |
| `cmake -S . -B build` | Configura o projeto e gera arquivos de build em `build/`. |
| `cmake --build build` | Compila o executável `game`. |
| `cd build && ./game` | Executa o jogo com paths de assets corretos. |

### VS Code (`.vscode/tasks.json`)

| Task | Comando | Descrição |
| ---- | ------- | --------- |
| `C/C++: gcc build active file` | `/usr/bin/gcc ${file} ... -lraylib ...` | Compila o arquivo ativo com flags de link para raylib e bibliotecas Linux. |

> A task do VS Code é útil para estudo local, mas o fluxo principal documentado do projeto é CMake.

---

## Workflow de Build

### Build Limpo

```bash
cmake -S . -B build
cmake --build build
```

### Rebuild após Alterações

```bash
cmake --build build
```

### Limpar Artefatos

`build/` é ignorado pelo Git. Para refazer tudo do zero, remova a pasta manualmente e configure novamente:

```bash
rm -rf build
cmake -S . -B build
cmake --build build
```

---

## Estratégia de Distribuição

### Build Local

O projeto foi estruturado para uso local. O binário `build/game` depende de:

- raylib disponível no sistema;
- bibliotecas gráficas/áudio da plataforma;
- pasta `assets/` preservada no caminho relativo esperado.

### Empacotamento Manual

Para distribuir manualmente, preserve a relação entre binário e assets:

```bash
release/
├── game
└── assets/
    ├── audio/
    └── sprites/
```

Nesse formato, os caminhos do código precisariam ser ajustados de `../assets/...` para `./assets/...`, ou o binário precisaria ficar em um subdiretório equivalente a `build/`.

---

## Healthchecks

### Verificar Toolchain

```bash
cc --version
cmake --version
```

### Verificar Configuração CMake

```bash
cmake -S . -B build
```

Resultado esperado: CMake encontra raylib e gera arquivos de build sem erro.

### Verificar Build

```bash
cmake --build build
```

Resultado esperado: executável `build/game` gerado.

### Verificar Runtime

```bash
cd build
./game
```

Resultado esperado:

```text
1. Janela "Slot Machine Game" abre em 400 x 400.
2. Máquina é renderizada no centro.
3. Clique esquerdo inicia spin e toca som de roleta.
4. Reels animam e depois exibem símbolos finais.
5. Saldo muda conforme vitória ou derrota.
6. Com saldo zero, game over aparece e TRY AGAIN reinicia.
```

---

## Execução de Rotina

Checklist para desenvolvimento local:

```bash
# 1. Entrar no projeto
cd c-game-raylib

# 2. Configurar build, se ainda não existir
cmake -S . -B build

# 3. Compilar
cmake --build build

# 4. Executar com caminhos de assets corretos
cd build
./game
```
