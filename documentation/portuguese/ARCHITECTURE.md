# Arquitetura do Projeto

## Justificativa da Arquitetura

O projeto adota uma **arquitetura procedural modular em C**, centrada em um loop de jogo da raylib e em uma máquina de estados simples para controlar a slot machine. Essa escolha resolve três problemas centrais deste projeto:

1. **Baixa complexidade para aprendizado**: O fluxo principal fica visível em poucos arquivos, facilitando estudar inicialização, atualização, desenho e encerramento.
2. **Integração direta com raylib**: A lógica usa funções da raylib sem uma camada intermediária, o que reduz boilerplate em um projeto acadêmico pequeno.
3. **Estado explícito do jogo**: Dinheiro, reels, timers, texturas, sons e estados ficam em variáveis globais controladas por funções de ciclo de vida.

A arquitetura não tenta aplicar Clean Architecture ou orientação a objetos. Para o tamanho atual, a separação por responsabilidade entre `main.c`, `config.h`, `game.h` e `game.c` é suficiente e mantém o foco no comportamento do jogo.

---

## Visualização da Arquitetura

```text
┌─────────────────────────────────────────────────────────────┐
│                         src/main.c                          │
│  InitWindow → InitAudioDevice → InitGame → loop principal   │
│  UpdateGame → DrawGame → unload recursos → CloseWindow      │
└──────────────────────────────┬──────────────────────────────┘
                               │
┌──────────────────────────────▼──────────────────────────────┐
│                       src/core/game.c                       │
│  Estados, sorteio dos reels, timers, animação, vitória,     │
│  derrota, tela de game over, desenho de sprites e sons.     │
└───────────────┬───────────────────────────────┬─────────────┘
                │                               │
┌───────────────▼──────────────┐  ┌─────────────▼──────────────┐
│      src/config/config.h     │  │           assets/          │
│  Constantes de janela, FPS,  │  │  Sprites PNG, animações e  │
│  dinheiro, custo e prêmio.   │  │  sons MP3 carregados em runtime.│
└──────────────────────────────┘  └────────────────────────────┘
```

---

## Fluxo de Dados — Rodada da Slot Machine

### Spin do Jogador

```text
1. O jogador clica com o botão esquerdo do mouse.
2. UpdateGame() detecta o clique no estado SLOT_STATIC.
3. StartSpin() desconta WITHDRAW_MONEY do saldo.
4. StartSpin() muda slot_state para SLOT_SPINNING e toca roleta.mp3.
5. Durante 11 segundos, UpdateGame() sorteia reels[0..2] a cada frame.
6. DrawGame() exibe a animação mistery1.png até mistery10.png nos três reels.
7. Quando spin_timer chega a zero, o estado muda para SLOT_RESULT.
8. Se os três reels forem iguais, WinGame() adiciona GAIN_MONEY.
9. Se não forem iguais, LoseGame() ativa mensagem de perda e shake visual.
10. No próximo clique, o jogo volta para SLOT_STATIC ou entra em GAME_OVER.
```

### Game Over

```text
1. Em SLOT_RESULT, se money <= 0 e o jogador clicar, game_state muda para GAME_OVER.
2. O som gameover.mp3 é reproduzido.
3. DrawGame() delega para DrawGameOver().
4. DrawGameOver() desenha a tela preta, mensagem e botão TRY AGAIN.
5. Clique no botão reinicia dinheiro, slot_state e game_state.
```

---

## Dependências entre Módulos

O ponto de entrada depende diretamente da configuração e do core do jogo:

```c
#include "./config/config.h"
#include "./core/game.c"
```

`src/core/game.c` inclui `game.h`, `config.h`, raylib e bibliotecas padrão (`stdlib.h`, `stdio.h`, `time.h`). O arquivo `game.h` expõe funções de ciclo de vida e variáveis externas usadas pelo entrypoint.

> Observação técnica: `main.c` inclui `game.c` diretamente. Isso funciona porque o `CMakeLists.txt` compila apenas `src/*.c`; nessa organização, a implementação do core entra na mesma unidade de compilação de `main.c`. Em um projeto maior, o caminho mais comum seria compilar `src/core/game.c` separadamente e incluir apenas `game.h`.

---

## Módulos do Sistema

| Módulo                | Responsabilidade                                                                              |
| --------------------- | --------------------------------------------------------------------------------------------- |
| `src/main.c`          | Inicializa janela e áudio, define FPS, executa o loop principal e libera recursos principais. |
| `src/config/config.h` | Define constantes de janela, título, dinheiro inicial, custo, ganho e FPS.                    |
| `src/core/game.h`     | Declara enums, funções públicas do core e variáveis externas compartilhadas.                  |
| `src/core/game.c`     | Implementa estados, sorteios, animações, desenho, regras de vitória/perda e game over.        |
| `assets/sprites/`     | Contém a máquina, símbolos finais e quadros de animação dos reels.                            |
| `assets/audio/`       | Contém efeitos sonoros usados pelo spin e pelo game over.                                     |
| `CMakeLists.txt`      | Define o build CMake, padrão C11, saída em `build/` e link com raylib.                        |
