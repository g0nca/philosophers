# 🍝 Philosophers - Dining Philosophers Problem

<div align="center">

![42 School](https://img.shields.io/badge/42-School-000000?style=for-the-badge&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Threads](https://img.shields.io/badge/Threads-FF6B6B?style=for-the-badge)
![Grade](https://img.shields.io/badge/Grade-100%2F100-success?style=for-the-badge)
**Solução completa para o problema clássico do jantar dos filósofos usando threads e mutexes**

[Sobre](#-sobre-o-projeto) • 
[Conceitos](#-conceitos-aprendidos) • 
[Compilação](#️-compilação) • 
[Uso](#-uso) • 
[Estrutura](#-estrutura-do-projeto) • 
[Funções](#-documentação-de-funções)

</div>

---

## 📋 Sobre o Projeto

O **Philosophers** é um projeto que implementa uma solução para o problema clássico de sincronização de processos conhecido como "O Jantar dos Filósofos", proposto por Edsger Dijkstra em 1965.

### 🎯 Objetivo

Criar uma simulação onde N filósofos sentam-se numa mesa circular, alternando entre três estados: **comer**, **pensar** e **dormir**. Cada filósofo precisa de dois garfos para comer, mas há apenas um garfo entre cada par de filósofos.

### 🚫 Desafios

- **Deadlock**: Evitar que todos os filósofos peguem um garfo simultaneamente
- **Starvation**: Garantir que nenhum filósofo morra de fome
- **Data Races**: Sincronizar corretamente o acesso a recursos compartilhados
- **Performance**: Detectar mortes em menos de 10ms


**Concepts**
(https://g0nca.github.io/philosophers/)

---

## 🧠 Conceitos Aprendidos

### 1. **Programação Concorrente**
- Criação e gestão de threads POSIX (`pthread`)
- Paralelismo vs Concorrência
- Contextos de execução independentes

### 2. **Sincronização de Threads**
- **Mutexes** (Mutual Exclusion)
- **Critical Sections** (seções críticas)
- Proteção de recursos compartilhados

### 3. **Problemas Clássicos**
- **Deadlock**: Impasse circular na aquisição de recursos
- **Race Conditions**: Condições de corrida em acessos concorrentes
- **Starvation**: Inanição de threads por falta de recursos

### 4. **Sincronização de Tempo**
- `gettimeofday()` para timestamps precisos
- Sleeps inteligentes com verificações periódicas
- Detecção de eventos time-sensitive

### 5. **Design Patterns**
- **Resource Ordering**: Ordem consistente de aquisição de locks
- **Monitor Pattern**: Thread dedicada para monitoramento
- **Thread-Safe Operations**: Operações protegidas por mutexes

---

## 🛠️ Compilação

### Requisitos
- GCC ou Clang
- Make
- Sistema POSIX compatível (Linux, macOS)

### Comandos

```bash
# Compilar
make

# Limpar objetos
make clean

# Limpar tudo
make fclean

# Recompilar
make re
```

### Flags de Compilação
```bash
-Wall -Wextra -Werror  # Warnings rigorosos
-pthread               # Suporte a threads POSIX
-g                     # Símbolos de debug
```

---

## 🎮 Uso

### Sintaxe
```bash
./philosophers number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Parâmetros

| Parâmetro | Descrição | Limites |
|-----------|-----------|---------|
| `number_of_philosophers` | Número de filósofos e garfos | 1-200 |
| `time_to_die` | Tempo máximo sem comer (ms) | ≥ 60 |
| `time_to_eat` | Tempo para comer (ms) | ≥ 60 |
| `time_to_sleep` | Tempo para dormir (ms) | ≥ 60 |
| `[number_of_times...]` | Refeições necessárias (opcional) | ≥ 1 |

### Exemplos

```bash
# Ninguém deve morrer (loop infinito)
./philosophers 5 800 200 200

# Alguém deve morrer em ~310ms
./philosophers 4 310 200 100

# Cada filósofo come 7 vezes
./philosophers 5 800 200 200 7

# Caso especial: 1 filósofo
./philosophers 1 800 200 200

# Teste de estresse: 200 filósofos
./philosophers 200 800 200 200
```

### Formato de Output

```
timestamp_in_ms X has taken a fork
timestamp_in_ms X is eating
timestamp_in_ms X is sleeping
timestamp_in_ms X is thinking
timestamp_in_ms X died
```

**Exemplo real:**
```
0 [1] has taken a fork
0 [1] has taken a fork
0 [1] is eating
0 [3] has taken a fork
0 [3] has taken a fork
0 [3] is eating
200 [1] is sleeping
200 [3] is sleeping
300 [1] is thinking
310 [2] died
```

---

## 📁 Estrutura do Projeto

```
philosophers/
├── Makefile
├── README.md
├── inc/
│   └── philosophers.h          # Headers e estruturas
└── srcs/
    ├── main.c                  # Entry point e orquestração
    ├── check_args.c            # Validação de argumentos
    ├── init_table.c            # Inicialização da simulação
    ├── philosophing.c          # Loop principal dos filósofos
    ├── philosophing_utils.c    # Funções auxiliares
    ├── philos_monitor.c        # Thread de monitoramento
    └── util.c                  # Utilitários gerais
```

### Arquitetura

```
┌─────────────────────────────────────────────────┐
│              MAIN THREAD                        │
│  ┌────────────────────────────────────────┐    │
│  │  1. Parsing & Validação                │    │
│  │  2. Inicialização de estruturas        │    │
│  │  3. Criação de threads                 │    │
│  └────────────────────────────────────────┘    │
│                                                  │
│  ┌────────────────────────────────────────┐    │
│  │  MONITOR LOOP (philos_monitor)         │    │
│  │  - Verifica mortes                     │    │
│  │  - Verifica conclusão                  │    │
│  └────────────────────────────────────────┘    │
│                                                  │
│  ┌────────────────────────────────────────┐    │
│  │  JOIN & CLEANUP                        │    │
│  │  - pthread_join()                      │    │
│  │  - Destroy mutexes                     │    │
│  └────────────────────────────────────────┘    │
└─────────────────────────────────────────────────┘

        ▼ ▼ ▼ ▼ ▼ (spawned threads)

┌──────────────┐  ┌──────────────┐  ┌──────────────┐
│  PHILO 1     │  │  PHILO 2     │  │  PHILO N     │
│  (Thread)    │  │  (Thread)    │  │  (Thread)    │
│              │  │              │  │              │
│  LOOP:       │  │  LOOP:       │  │  LOOP:       │
│  - Think     │  │  - Think     │  │  - Think     │
│  - Take forks│  │  - Take forks│  │  - Take forks│
│  - Eat       │  │  - Eat       │  │  - Eat       │
│  - Sleep     │  │  - Sleep     │  │  - Sleep     │
└──────────────┘  └──────────────┘  └──────────────┘
```

---

## 🗂️ Estruturas de Dados

### `t_philo` - Estrutura do Filósofo

```c
typedef struct s_philo
{
    int                 philo_nbr;      // ID do filósofo (1 a N)
    int                 meal_nbr;       // Número de refeições feitas
    uint64_t            last_meal;      // Timestamp da última refeição
    pthread_t           thread;         // Thread do filósofo
    pthread_mutex_t     l_fork;         // Mutex do garfo esquerdo (próprio)
    pthread_mutex_t     *r_fork;        // Ponteiro para garfo direito (vizinho)
    struct s_table      *table;         // Ponteiro para dados globais
}   t_philo;
```

**Campos importantes:**
- `last_meal`: Crucial para detecção de morte
- `l_fork`: Cada filósofo "possui" um garfo
- `r_fork`: Aponta para o garfo do próximo filósofo (compartilhado)

### `t_table` - Estrutura Global

```c
typedef struct s_table
{
    int             n_philos;           // Número de filósofos
    int             t_2eat;             // Tempo para comer (ms)
    int             t_2sleep;           // Tempo para dormir (ms)
    int             t_2die;             // Tempo máximo sem comer (ms)
    int             max_rounds;         // Número de refeições (-1 = infinito)
    int             how_many_r_full;    // Contador de filósofos satisfeitos
    bool            philo_dead;         // Flag: algum filósofo morreu?
    bool            philos_full;        // Flag: todos comeram o suficiente?
    uint64_t        start_time;         // Timestamp do início
    pthread_mutex_t sync;               // Mutex de sincronização global
    t_philo         philo[200];         // Array de filósofos
}   t_table;
```

**Campos importantes:**
- `sync`: Protege todas as variáveis compartilhadas
- `philo_dead` / `philos_full`: Controlam o fim da simulação

---

## 📚 Documentação de Funções

### 🎯 Funções Principais

#### `int main(int ac, char **av)`
**Descrição**: Entry point do programa  
**Fluxo**:
1. Valida argumentos (`check_args`)
2. Inicializa mutex global
3. Cria threads dos filósofos
4. Inicia monitoramento
5. Aguarda threads terminarem (join)
6. Destrói mutexes

**Retorno**: `0` em sucesso, `1` em erro

---

#### `void *philosophing(void *philo)`
**Descrição**: Função executada por cada thread (filósofo)  
**Parâmetros**: Ponteiro para `t_philo`  
**Comportamento**:
```c
while (!simulation_ended)
{
    take_forks();          // Pega 2 garfos
    eat();                 // Come por t_2eat ms
    sleep_and_think();     // Dorme e pensa
}
```

**Estratégia anti-deadlock**:
- Filósofos **pares** pegam garfo direito → esquerdo
- Filósofos **ímpares** pegam garfo esquerdo → direito

**Retorno**: `NULL`

---

#### `void philos_monitor(t_table *table)`
**Descrição**: Loop de monitoramento (main thread)  
**Responsabilidades**:
1. Verifica se algum filósofo morreu (`now - last_meal > t_2die`)
2. Verifica se todos completaram refeições
3. Seta flags `philo_dead` ou `philos_full`

**Timing**: Verifica a cada 1ms (`usleep(1000)`)

**Critical**: Esta função **termina** a simulação!

---

### 🔧 Funções de Controle

#### `void start_simulation(t_table *table)`
```c
void start_simulation(t_table *table)
{
    int x = 0;
    while (x < table->n_philos)
    {
        pthread_create(&table->philo[x].thread, NULL, 
                      philosophing, &table->philo[x]);
        x++;
    }
}
```
**Descrição**: Cria uma thread para cada filósofo

---

#### `void join_threads(t_table *table)`
```c
void join_threads(t_table *table)
{
    int x = 0;
    while (x < table->n_philos)
    {
        pthread_join(table->philo[x].thread, NULL);
        x++;
    }
}
```
**Descrição**: Aguarda todas as threads terminarem  
**Importante**: `pthread_join()` **bloqueia** até a thread terminar

---

#### `void destroy_mutex(t_table *table)`
**Descrição**: Libera recursos (mutexes)  
**Ordem**:
1. Destroi mutexes dos garfos (um por filósofo)
2. Destroi mutex global (`sync`)

---

### 🍴 Funções de Ação

#### `bool take_forks(t_philo *p)`
**Descrição**: Decide ordem de aquisição de garfos  
**Lógica**:
```c
if (philo_nbr % 2 == 0)
    take_right_then_left();   // Pares
else
    take_left_then_right();   // Ímpares
```

---

#### `bool take_right_then_left(t_philo *philo)`
**Descrição**: Filósofos **PARES** pegam garfo direito primeiro  
**Fluxo**:
1. Verifica se simulação terminou
2. `pthread_mutex_lock(r_fork)`
3. Imprime "has taken a fork"
4. Verifica novamente
5. `pthread_mutex_lock(&l_fork)`
6. Imprime "has taken a fork"

**Retorno**: `true` se pegou ambos, `false` se falhou

---

#### `bool eat(t_philo *philo)`
**Descrição**: Filósofo come  
**Passos críticos**:
```c
1. pthread_mutex_lock(&table->sync);
2. meal_nbr++;
3. last_meal = ft_time_ms();  ← CRUCIAL!
4. pthread_mutex_unlock(&table->sync);
5. Imprime "is eating"
6. ft_usleep_check(t_2eat);
7. Verifica se completou refeições
8. Libera garfos
```

**⚠️ IMPORTANTE**: `last_meal` deve ser atualizado **ANTES** de imprimir, protegido por mutex!

---

#### `bool sleep_and_think(t_philo *philo)`
**Descrição**: Filósofo dorme e pensa  
**Fluxo**:
1. Imprime "is sleeping"
2. Dorme por `t_2sleep` ms
3. Imprime "is thinking"

---

### 🛠️ Funções Auxiliares

#### `bool simulation_ended(t_philo *philo)`
```c
bool simulation_ended(t_philo *philo)
{
    bool ended;
    pthread_mutex_lock(&philo->table->sync);
    ended = philo->table->philo_dead || philo->table->philos_full;
    pthread_mutex_unlock(&philo->table->sync);
    return (ended);
}
```
**Descrição**: Verifica se a simulação terminou (thread-safe)

---

#### `bool ft_message(t_philo *philo, const char *message)`
```c
bool ft_message(t_philo *philo, const char *message)
{
    pthread_mutex_lock(&philo->table->sync);
    if (philo->table->philo_dead || philo->table->philos_full)
    {
        pthread_mutex_unlock(&philo->table->sync);
        return (false);
    }
    printf("%lu [%d] %s\n", ft_time_ms() - philo->table->start_time,
           philo->philo_nbr, message);
    pthread_mutex_unlock(&philo->table->sync);
    return (true);
}
```
**Descrição**: Imprime mensagem apenas se simulação não terminou  
**Thread-safe**: Protegido por mutex global

---

#### `void ft_usleep_check(uint64_t ms, t_philo *philo)`
```c
void ft_usleep_check(uint64_t ms, t_philo *philo)
{
    uint64_t start = ft_time_ms();
    
    while (ft_time_ms() - start < ms)
    {
        if (simulation_ended(philo))
            break;
        usleep(500);  // 500 microsegundos
    }
}
```
**Descrição**: Sleep inteligente com verificações periódicas  
**Por que?**: Garante resposta rápida quando simulação termina

---

#### `void initial_delay(t_philo *philo)`
```c
void initial_delay(t_philo *philo)
{
    if (philo->philo_nbr % 2 == 0)
        ft_usleep_check(10, philo);
}
```
**Descrição**: Delay de 10ms para filósofos pares  
**Objetivo**: Dessincronizar início e evitar rush inicial

---

#### `void *ft_one_philo(t_philo *philo)`
```c
void *ft_one_philo(t_philo *philo)
{
    pthread_mutex_lock(&philo->l_fork);
    ft_message(philo, "has taken a fork");
    ft_usleep_check(philo->table->t_2die, philo);
    pthread_mutex_unlock(&philo->l_fork);
    return (NULL);
}
```
**Descrição**: Caso especial de 1 filósofo  
**Comportamento**: Pega 1 garfo e aguarda morrer (não pode comer)

---

### ⚙️ Funções Utilitárias

#### `uint64_t ft_time_ms(void)`
```c
uint64_t ft_time_ms(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
```
**Descrição**: Obtém timestamp atual em milissegundos  
**Uso**: Cálculo de tempos e detecção de morte

---

#### `int ft_atoi(const char *str)`
**Descrição**: Converte string para inteiro  
**Diferença do original**: Aceita apenas números positivos

---

#### `void error_exit(const char *str)`
**Descrição**: Imprime mensagem de erro e termina programa  
**Uso**: Erros de validação de argumentos

---

## 🔄 Fluxograma Completo

```
                    ┌─────────────────────┐
                    │   INÍCIO (main)     │
                    └──────────┬──────────┘
                               │
                    ┌──────────▼──────────┐
                    │  check_args()       │
                    │  - Valida argc      │
                    │  - Valida números   │
                    │  - Verifica limites │
                    └──────────┬──────────┘
                               │
                    ┌──────────▼──────────┐
                    │  init_table()       │
                    │  - Parse argumentos │
                    │  - Init variáveis   │
                    │  - Setup filósofos  │
                    │  - Init mutexes     │
                    └──────────┬──────────┘
                               │
                    ┌──────────▼──────────┐
                    │ start_simulation()  │
                    │                     │
                    │  for each philo:    │
                    │    pthread_create() │
                    └──────────┬──────────┘
                               │
                ┌──────────────┼──────────────┐
                │              │              │
       ┌────────▼────────┐     │     ┌───────▼────────┐
       │ Thread Philo 1  │     │     │ Thread Philo N │
       │                 │     │     │                │
       │ philosophing()  │    ...    │ philosophing() │
       └────────┬────────┘     │     └───────┬────────┘
                │              │             │
                │      ┌───────▼──────┐      │
                │      │  MAIN THREAD │      │
                │      │              │      │
                │      │ philos_      │      │
                │      │ monitor()    │      │
                │      │              │      │
                │      │ Loop:        │      │
                │      │ - Check morte│      │
                │      │ - Check full │      │
                │      └───────┬──────┘      │
                │              │             │
                └──────────────┼─────────────┘
                               │
                    ┌──────────▼──────────┐
                    │  join_threads()     │
                    │                     │
                    │  for each philo:    │
                    │    pthread_join()   │
                    └──────────┬──────────┘
                               │
                    ┌──────────▼──────────┐
                    │  destroy_mutex()    │
                    │  - Destroy forks    │
                    │  - Destroy sync     │
                    └──────────┬──────────┘
                               │
                    ┌──────────▼──────────┐
                    │   FIM (return 0)    │
                    └─────────────────────┘
```

### Fluxo de Cada Thread (philosophing)

```
┌─────────────────────────────────────┐
│      philosophing(philo)            │
└──────────────┬──────────────────────┘
               │
        ┌──────▼──────┐
        │ n_philos==1?│
        └──┬────────┬─┘
     YES   │        │ NO
           │        │
    ┌──────▼────┐   │
    │ ft_one_   │   │
    │ philo()   │   │
    └──────┬────┘   │
           │        │
        return   ┌──▼─────────┐
                 │initial_    │
                 │delay()     │
                 └──┬─────────┘
                    │
        ┌───────────▼───────────┐
        │ while (!simulation_   │
        │       ended())        │
        └───────────┬───────────┘
                    │
         ┌──────────▼──────────┐
         │   take_forks()      │
         │   ┌─────────────┐   │
         │   │ Par: R → L  │   │
         │   │ Ímpar: L → R│   │
         │   └─────────────┘   │
         └──────────┬──────────┘
                    │
         ┌──────────▼──────────┐
         │      eat()          │
         │  ┌──────────────┐   │
         │  │ meal_nbr++   │   │
         │  │ last_meal=now│   │
         │  │ sleep(t_2eat)│   │
         │  │ unlock forks │   │
         │  └──────────────┘   │
         └──────────┬──────────┘
                    │
         ┌──────────▼──────────┐
         │ sleep_and_think()   │
         │  ┌──────────────┐   │
         │  │ is sleeping  │   │
         │  │ sleep(t_2sleep)│  │
         │  │ is thinking  │   │
         │  └──────────────┘   │
         └──────────┬──────────┘
                    │
                    └──────┐
                           │
                      ┌────▼────┐
                      │ Loop de │
                      │ volta   │
                      └─────────┘
```

---

## 🧪 Testes e Debugging

### Testes Básicos

```bash
# 1. Ninguém morre
./philosophers 5 800 200 200
# Deve rodar indefinidamente

# 2. Morte previsível
./philosophers 4 310 200 100
# Alguém deve morrer em ~310ms

# 3. Número de refeições
./philosophers 5 800 200 200 7
# Output: "Every Philosopher has eaten 7 times"

# 4. Um filósofo
./philosophers 1 800 200 200
# Output: 
# 0 [1] has taken a fork
# 800 [1] died

# 5. Muitos filósofos
./philosophers 200 800 200 200
# Deve funcionar sem travar
```

### Ferramentas de Debug

#### Valgrind - Memory Leaks
```bash
valgrind --leak-check=full ./philosophers 5 800 200 200 7
```
**Esperado**: `All heap blocks were freed -- no leaks are possible`

#### Helgrind - Data Races
```bash
valgrind --tool=helgrind ./philosophers 5 800 200 200
```
**Buscar**: "Possible data race", "lock order"

#### GDB - Debugging
```bash
gcc -g -pthread srcs/*.c -I./inc -o philo_debug
gdb ./philo_debug

(gdb) run 5 800 200 200
(gdb) bt          # Backtrace se crashar
(gdb) print var   # Inspecionar variáveis
```

---

## ⚠️ Problemas Comuns e Soluções

### 1. Deadlock (Tudo Trava)

**Sintoma**: Programa para de responder

**Causas**:
- Ordem inconsistente de locks
- Esquecer de fazer unlock

**Solução**:
```c
// ✅ CORRETO: Ordem diferente
if (id % 2 == 0)
    lock(R) → lock(L)
else
    lock(L) → lock(R)
```

### 2. Data Race

**Sintoma**: Helgrind reporta "conflicting access"

**Causas**:
- Acessar `last_meal` sem mutex
- Ler/escrever flags sem proteção

**Solução**:
```c
// ✅ SEMPRE usar mutex
pthread_mutex_lock(&sync);
philo->last_meal = ft_time_ms();
pthread_mutex_unlock(&sync);
```

### 3. Mensagens Após Morte

**Sintoma**: Output mostra "is eating" depois de "died"

**Causa**: Não verificar `philo_dead` antes de imprimir

**Solução**:
```c
// ✅ Verificar estado
if (philo_dead || philos_full)
    return (false);  // Não imprime
```

### 4. Morte Não Detectada

**Sintoma**: Filósofo deveria morrer mas não morre

**Causas**:
- `last_meal` não atualizado
- Monitor com delay muito grande

**Solução**:
```c
// ✅ Atualizar last_meal ANTES de comer
pthread_mutex_lock(&sync);
philo->last_meal = ft_time_ms();
pthread_mutex_unlock(&sync);
```

---

## 📖 Recursos e Referências

### Documentação POSIX Threads
- `man pthread_create`
- `man pthread_join`
- `man pthread_mutex_lock`
- `man pthread_mutex_unlock`
- `man gettimeofday`

### Artigos e Tutoriais
- [Dining Philosophers Problem - Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/)
- [Deadlock Prevention](https://www.geeksforgeeks.org/deadlock-prevention/)

### Livros Recomendados
- **"Operating System Concepts"** - Silberschatz, Galvin, Gagne
- **"Modern Operating Systems"** - Andrew S. Tanenbaum
- **"Programming with POSIX Threads"** - David R. Butenhof

---

## 👤 Autor

**ggomes-v**  
42 Porto - 2025

---

## 📄 Licença

Este projeto é desenvolvido como parte do currículo da 42 School.

---

<div align="center">

**⭐ Se este projeto te ajudou, considera dar uma estrela! ⭐**

Made with 💜 and lots of ☕

</div>
