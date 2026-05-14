# Pré-requisitos e Desempenho

## Dependências de Sistema

### Runtime e Build

| Dependência | Versão Mínima | Verificação |
| ----------- | ------------- | ----------- |
| **Compilador C** | GCC ou Clang com suporte a C11 | `cc --version` |
| **CMake** | `>= 3.10` | `cmake --version` |
| **raylib** | Compatível com `find_package(raylib REQUIRED)` | `pkg-config --libs raylib` ou teste de CMake |
| **Git** | Qualquer versão moderna | `git --version` |

### Bibliotecas Linux Comuns para raylib

| Dependência | Função |
| ----------- | ------ |
| `libasound2-dev` | Backend de áudio ALSA. |
| `libx11-dev` | Janela e entrada via X11. |
| `libxrandr-dev` | Resolução e monitor. |
| `libxi-dev` | Entrada de dispositivos. |
| `libgl1-mesa-dev` / `libglu1-mesa-dev` | OpenGL/Mesa. |
| `libxcursor-dev` | Cursor X11. |
| `libxinerama-dev` | Múltiplos monitores. |
| `libwayland-dev` / `libxkbcommon-dev` | Suporte Wayland quando aplicável. |

### Ferramentas Opcionais

| Ferramenta | Função |
| ---------- | ------ |
| **VS Code** | Usar as configurações versionadas em `.vscode/`. |
| **Extensão C/C++** | IntelliSense, associação de headers e execução da task GCC. |
| **Ninja** | Gerador CMake alternativo, se preferido. |

---

## Dependências do Projeto

### Código

| Item | Categoria | Observação |
| ---- | --------- | ---------- |
| `src/main.c` | Entry point | Inicializa janela e loop principal. |
| `src/core/game.c` | Core | Implementa a slot machine. |
| `src/core/game.h` | Header | Declara funções, enums e externs. |
| `src/config/config.h` | Configuração | Constantes de janela, FPS e economia. |

### Assets de Produção

| Diretório | Conteúdo | Obrigatório |
| --------- | -------- | ----------- |
| `assets/sprites/` | Máquina e símbolos finais. | Sim |
| `assets/sprites/animation/` | 10 quadros de animação dos reels. | Sim |
| `assets/audio/` | Sons MP3 de roleta e game over. | Sim para experiência completa |

### Gerenciadores de Pacote

O projeto não usa `npm`, `pip`, `vcpkg` ou outro gerenciador próprio. A dependência principal é a raylib instalada no sistema e descoberta pelo CMake.

---

## Hardware Sugerido

### Desenvolvimento Local

| Recurso | Mínimo | Recomendado |
| ------- | ------ | ----------- |
| **RAM** | 2 GB | 4 GB ou mais |
| **CPU** | 1 core | 2 cores ou mais |
| **Disco** | 200 MB para projeto e build | 1 GB livre se compilar raylib localmente |
| **GPU** | Suporte OpenGL básico | Driver gráfico atualizado |
| **SO** | Linux, macOS ou Windows com toolchain C | Linux com raylib instalada |

### Execução do Jogo

| Recurso | Observação |
| ------- | ---------- |
| **Janela** | 400 x 400 pixels. |
| **FPS alvo** | 40 FPS conforme `DEFAULT_FPS`. |
| **Áudio** | Dispositivo de áudio funcional para MP3. |
| **Entrada** | Mouse para iniciar spin e reiniciar. |

### Portas Utilizadas

O projeto não utiliza portas de rede. A aplicação é um jogo desktop local, sem servidor HTTP, banco de dados ou comunicação externa.
