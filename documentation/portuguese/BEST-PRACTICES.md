# Boas Práticas

## Princípios de Projeto

### Responsabilidade Única

Cada arquivo concentra uma responsabilidade clara:

- **`main.c`**: Ciclo de vida da aplicação raylib.
- **`config.h`**: Constantes de configuração e balanceamento.
- **`game.h`**: Contrato público do módulo de jogo.
- **`game.c`**: Regras, estados, animação, desenho e interação.
- **`assets/`**: Recursos externos usados em runtime.

### Baixo Acoplamento Possível

O jogo é naturalmente acoplado à raylib, mas esse acoplamento fica concentrado em `main.c` e `game.c`. A configuração numérica fica isolada em `config.h`.

### Clareza sobre Estado Global

O projeto usa variáveis globais para manter o estado do jogo. Em um jogo pequeno, isso facilita leitura e aprendizado. Em um jogo maior, seria melhor agrupar esse estado em uma struct `Game` e passá-la para as funções.

---

## Tratamento de Erros

### Assets

| Situação | Estado atual | Boa prática recomendada |
| -------- | ------------ | ----------------------- |
| Sprite ausente | `LoadTexture()` é chamado sem checagem explícita. | Verificar `texture.id` após carregar e encerrar com mensagem clara se falhar. |
| Som ausente | `LoadSound()` é chamado sem checagem explícita. | Validar o recurso carregado e evitar `PlaySound()` em recurso inválido. |
| Caminho relativo errado | O código espera execução a partir de `build/`. | Documentar o diretório correto de execução ou resolver paths com base no executável. |

### Runtime

| Camada | Estratégia atual |
| ------ | ---------------- |
| **Entrada** | Apenas clique esquerdo do mouse inicia spin e confirma resultado. |
| **Game Over** | Estado separado com botão `TRY AGAIN` para reiniciar saldo e estado. |
| **Timers** | Reduzidos com `GetFrameTime()` e usados para spin, mensagem de perda e shake. |

---

## Testes

### Tipos de Teste Configurados

| Tipo | Framework | Configuração |
| ---- | --------- | ------------ |
| **Automatizado** | Não configurado | Não há suíte de testes versionada no projeto atual. |
| **Build** | CMake + compilador C | `cmake -S . -B build` e `cmake --build build`. |
| **Manual** | Execução do jogo | Abrir `build/game`, clicar para girar, validar vitória, derrota e game over. |

### Checklist Manual

```text
1. Compilar sem erros.
2. Executar a partir de build/.
3. Confirmar que a janela abre em 400 x 400.
4. Confirmar que o clique inicia o spin e toca roleta.mp3.
5. Confirmar que a animação aparece durante o spin.
6. Confirmar que vitória aumenta o dinheiro.
7. Confirmar que derrota mostra PERDEU!! e aplica shake.
8. Confirmar que saldo zero leva para GAME_OVER.
9. Confirmar que TRY AGAIN reinicia o jogo.
```

### Cobertura

Não há coleta de cobertura configurada. Para evoluir o projeto, funções de regra pura, como cálculo de vitória e alteração de saldo, poderiam ser extraídas para facilitar testes unitários em C.

---

## Segurança

### Superfície de Segurança

O jogo não possui rede, autenticação, banco de dados, arquivos de usuário ou variáveis secretas. A superfície de segurança é baixa e limitada ao carregamento de arquivos locais.

| Aspecto | Implementação |
| ------- | ------------- |
| **Segredos** | Não há segredos versionados. |
| **Entrada externa** | Apenas mouse e fechamento da janela. |
| **Arquivos carregados** | PNG e MP3 de caminhos relativos dentro de `assets/`. |
| **Dados persistidos** | Nenhum dado persistido entre execuções. |

### Gestão de Arquivos Locais

`.gitignore` ignora artefatos e diretórios locais:

```text
build
raylib
.agent
.agents
.codex
```

Isso evita versionar binários, builds locais, checkout local da raylib e arquivos de agente.

---

## Riscos Técnicos Conhecidos

| Risco | Impacto | Recomendação |
| ----- | ------- | ------------ |
| `main.c` inclui `game.c` diretamente | Pode confundir manutenção e gerar duplicidade se `game.c` entrar no build separadamente. | Compilar `src/core/game.c` pelo CMake e incluir apenas `game.h` em `main.c`. |
| Assets usam `../assets/...` | Executar de outro diretório pode quebrar carregamento. | Padronizar execução a partir de `build/` ou resolver caminho absoluto no início. |
| Quadros de animação não são descarregados explicitamente | Vazamento de textura ao encerrar, pequeno no projeto atual. | Criar `UnloadGame()` para liberar texturas de animação e sons carregados. |
| `grito.mp3` não é usado | Asset versionado sem referência no código. | Remover se não for necessário ou integrar em evento de gameplay. |
| Sem testes automatizados | Regressões em regras podem passar despercebidas. | Extrair regras puras e adicionar testes unitários. |
