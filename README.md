# 🍝 Guia Completo do Projeto Philosophers

## 📚 Conceitos Fundamentais

### O Problema do Jantar dos Filósofos
- **N filósofos** sentados em uma mesa circular
- **N garfos** (um entre cada par de filósofos)
- Cada filósofo precisa de **2 garfos** para comer
- Ações: **PENSAR** → **PEGAR GARFOS** → **COMER** → **DORMIR** → repetir

### Desafios
1. **Deadlock**: Todos pegam o garfo da esquerda simultaneamente → ninguém consegue pegar o da direita
2. **Data Races**: Múltiplas threads acessando/modificando dados compartilhados
3. **Starvation**: Um filósofo nunca consegue comer
4. **Sincronização**: Detectar quando um filósofo morre

---

## 🏗️ Arquitetura da Solução

### Estruturas de Dados

```c
t_data (cada filósofo)
├── philo_nbr       → ID do filósofo (1 a N)
├── meal_nbr        → Quantas vezes comeu
├── last_meal       → Timestamp da última refeição
├── thread          → Thread pthread
├── l_fork          → Mutex do garfo esquerdo (próprio)
├── r_fork          → Ponteiro para garfo direito (do vizinho)
└── vars            → Ponteiro para variáveis globais

t_vars (dados globais)
├── n_philos        → Número de filósofos
├── t_2die          → Tempo máximo sem comer (ms)
├── t_2eat          → Tempo para comer (ms)
├── t_2sleep        → Tempo para dormir (ms)
├── max_rounds      → Número de refeições necessárias (-1 = infinito)
├── how_many_r_full → Contador de filósofos que completaram
├── philo_dead      → Flag: algum filósofo morreu?
├── philos_full     → Flag: todos comeram o suficiente?
├── philosophers[200] → Array de todos os filósofos
├── start_time      → Timestamp do início da simulação
└── sync            → Mutex para sincronização global
```

---

## 🔄 Fluxo de Execução

### 1️⃣ Main (philo.c)

```
main()
  ├── memset(&philo, 0, sizeof(t_vars))
  ├── init_philo()        → Parsing e inicialização
  ├── create_threads()    → Cria N threads (uma por filósofo)
  ├── monitor_philos()    → Loop de monitoramento (main thread)
  ├── join_threads()      → Aguarda todas as threads terminarem
  └── destroyer()         → Libera mutexes
```

### 2️⃣ Inicialização (init.c)

```
init_philo()
  ├── Valida argumentos (5 ou 6)
  ├── check_numbers()     → Apenas dígitos positivos?
  ├── Parseia argumentos (ft_atoi)
  ├── check_limits()      → Valores dentro dos limites?
  ├── init_vars()         → Inicializa variáveis globais
  │     └── last_meal = start_time para TODOS
  └── philos_start()      → Configura mutexes e ponteiros
        ├── Cria mutex l_fork para cada filósofo
        └── r_fork aponta para l_fork do próximo (circular)
```

### 3️⃣ Thread do Filósofo (philosophing.c)

```
philosophing()
  ├── Caso especial: 1 filósofo
  │     └── ft_one_philo() → pega 1 garfo e aguarda morte
  │
  ├── ft_waitphilo() → Delay para filósofos pares (10ms)
  │
  └── Loop infinito (while ft_checker_full_death):
        ├── ft_take_forks()
        │     ├── Par:   r_fork → l_fork
        │     └── Ímpar: l_fork → r_fork
        │
        ├── ft_philo_eat()
        │     ├── meal_nbr++
        │     ├── last_meal = now
        │     ├── print "is eating"
        │     ├── ft_usleep(t_2eat)
        │     └── unlock forks
        │
        └── ft_philo_sleep_think()
              ├── print "is sleeping"
              ├── ft_usleep(t_2sleep)
              └── print "is thinking"
```

### 4️⃣ Monitoramento (checker.c + philo.c)

```
monitor_philos() [main thread]
  └── Loop infinito:
        ├── ft_checker_philos(philo, &i)
        │     ├── checker_death()
        │     │     └── (now - last_meal) > t_2die?
        │     │           ├── Yes: philo_dead = true, print "died"
        │     │           └── No: continua
        │     │
        │     └── checker_full()
        │           └── how_many_r_full == n_philos?
        │                 └── Yes: philos_full = true
        │
        ├── i++ (próximo filósofo)
        ├── if (i >= n_philos) → i = 0
        └── usleep(100) → evita 100% CPU
```

---

## 🔐 Sincronização e Mutexes

### Mutexes Utilizados

1. **`l_fork` (um por filósofo)**
   - Representa o garfo físico
   - Deve ser locked antes de usar o garfo
   - Shared entre dois filósofos adjacentes

2. **`sync` (global)**
   - Protege variáveis compartilhadas:
     - `philo_dead`, `philos_full`
     - `how_many_r_full`
     - `last_meal`, `meal_nbr`
   - Usado para imprimir mensagens atomicamente

### Regras de Locking

#### ✅ CORRETO
```c
pthread_mutex_lock(&philo->sync);
// Acessa variáveis compartilhadas
pthread_mutex_unlock(&philo->sync);
```

#### ❌ INCORRETO (Data Race)
```c
if (philo->philo_dead)  // Lê sem lock!
    return;
```

#### ✅ Ordem de Locking (evita deadlock)
```c
// Filósofos PARES
lock(r_fork);  // Garfo direito primeiro
lock(l_fork);  // Depois esquerdo

// Filósofos ÍMPARES
lock(l_fork);  // Garfo esquerdo primeiro
lock(r_fork);  // Depois direito
```

---

## 🐛 Problemas Comuns e Soluções

### 1. Deadlock

**Problema**: Todos pegam o garfo esquerdo → ninguém consegue o direito

**Solução**: Ordem diferente para pares/ímpares
```c
if (philo_nbr % 2 == 0)
    lock(r_fork) → lock(l_fork)  // Pares
else
    lock(l_fork) → lock(r_fork)  // Ímpares
```

### 2. Data Race em `last_meal`

**Problema**:
```c
// Thread A (monitor): lê last_meal
if (now - philo->last_meal > t_2die)

// Thread B (philo): escreve last_meal
philo->last_meal = ft_time_ms();
```

**Solução**: Sempre usar mutex
```c
pthread_mutex_lock(&vars->sync);
philo->last_meal = ft_time_ms();
pthread_mutex_unlock(&vars->sync);
```

### 3. Mensagens Após Morte

**Problema**: Filósofo imprime "is eating" depois de outro morrer

**Solução**: Verificar `philo_dead` antes de imprimir
```c
bool ft_checker_message(t_data *philo, char *str)
{
    pthread_mutex_lock(&philo->vars->sync);
    if (philo->vars->philo_dead || philo->vars->philos_full)
    {
        pthread_mutex_unlock(&philo->vars->sync);
        return (false);  // Não imprime
    }
    printf("%lu %d %s\n", timestamp, id, str);
    pthread_mutex_unlock(&philo->vars->sync);
    return (true);
}
```

### 4. Mutexes Não Liberados

**Problema**: Lock sem unlock → deadlock permanente

**Solução**: Sempre fazer unlock em todos os caminhos
```c
pthread_mutex_lock(r_fork);
if (error_condition)
{
    pthread_mutex_unlock(r_fork);  // ✅ Libera antes de retornar
    return (false);
}
pthread_mutex_lock(l_fork);
// ... usar garfos ...
pthread_mutex_unlock(l_fork);
pthread_mutex_unlock(r_fork);
```

---

## 🧪 Testes Importantes

### Teste 1: Ninguém deve morrer
```bash
./philo 5 800 200 200
```
- 5 filósofos
- 800ms para morrer
- 200ms para comer
- 200ms para dormir

**Resultado esperado**: Loop infinito, ninguém morre

### Teste 2: Filósofo deve morrer
```bash
./philo 4 310 200 100
```
- 4 filósofos
- 310ms para morrer
- 200ms para comer
- 100ms para dormir

**Resultado esperado**: Um filósofo morre após ~310ms

### Teste 3: Todos comem X vezes
```bash
./philo 5 800 200 200 7
```
- 5 filósofos
- Cada um deve comer 7 vezes

**Resultado esperado**: "Every philosopher has eaten 7 times"

### Teste 4: Um filósofo só
```bash
./philo 1 800 200 200
```
**Resultado esperado**: 
```
0 1 has taken a fork
800 1 died
```

### Teste 5: Estresse (muitos filósofos)
```bash
./philo 200 800 200 200
```
**Resultado esperado**: Funciona sem crash

---

## 📊 Timing e Precisão

### `ft_usleep()` Inteligente
```c
void ft_usleep(uint64_t time, t_data *philo_x)
{
    uint64_t now = ft_time_ms();
    
    while (ft_time_ms() - now < time && !someone_dead(philo_x))
    {
        usleep(150);  // Sleep curto, verifica frequentemente
    }
}
```

**Por que não `usleep(time * 1000)`?**
- Precisamos verificar `someone_dead` frequentemente
- `usleep()` pode dormir mais que o pedido
- Loop com sleeps curtos = mais responsivo

---

## 🎯 Checklist Final

### Funcionalidades
- [ ] Parsing de argumentos correto
- [ ] Validação de limites (1-200 philos, times > 60ms)
- [ ] Inicialização de mutexes
- [ ] Criação de threads
- [ ] Loop de monitoramento
- [ ] Detecção de morte (within 10ms)
- [ ] Detecção de conclusão (todos comeram N vezes)
- [ ] Caso especial: 1 filósofo
- [ ] Destruição de mutexes
- [ ] Sem memory leaks

### Sincronização
- [ ] Sem data races
- [ ] Sem deadlocks
- [ ] Ordem correta de locks (par/ímpar diferente)
- [ ] Mensagens não impressas após morte
- [ ] `last_meal` atualizado com mutex

### Edge Cases
- [ ] 1 filósofo funciona
- [ ] 200 filósofos funciona
- [ ] Tempos muito curtos (60ms)
- [ ] max_rounds = 1
- [ ] max_rounds = -1 (infinito)

---

## 🔧 Compilação e Execução

### Compilar
```bash
cc -Wall -Wextra -Werror -pthread *.c -o philo
```

### Executar
```bash
./philo <n_philos> <t_die> <t_eat> <t_sleep> [max_meals]
```

### Exemplos
```bash
# Deve rodar indefinidamente
./philo 5 800 200 200

# Um deve morrer
./philo 4 310 200 100

# Todos comem 7 vezes
./philo 5 800 200 200 7
```

---

## 📝 Resumo das Correções Feitas

### `init.c`
✅ **Antes**: Só inicializava `philosophers[0].last_meal`  
✅ **Depois**: Loop inicializa TODOS os filósofos

### `philo.c`
✅ **Antes**: Loop de monitoramento confuso com `i = i + 0`  
✅ **Depois**: Loop claro com reset manual `if (i >= n) i = 0`

### `philosophing.c`
✅ **Antes**: Verificações após locks (perigoso)  
✅ **Depois**: Verificações antes de tentar pegar garfos

✅ **Antes**: Unlocks incompletos em caso de erro  
✅ **Depois**: Sempre libera todos os mutexes adquiridos

### `utils_philo.c`
✅ **Antes**: `ft_one_philo` só imprimia, não esperava  
✅ **Depois**: Espera `t_2die` antes de terminar

---

## 🎓 Conceitos Aprendidos

1. **Threads**: Execução paralela de código
2. **Mutexes**: Proteção de recursos compartilhados
3. **Deadlock**: Como evitar com ordenação consistente
4. **Data Races**: Importância de locks em acessos compartilhados
5. **Atomicidade**: Operações que não podem ser interrompidas
6. **Critical Sections**: Trechos de código que devem ser protegidos

---

## 💡 Dicas Extras

### Debug com prints
```c
printf("[DEBUG] Philo %d: trying to lock r_fork\n", id);
pthread_mutex_lock(r_fork);
printf("[DEBUG] Philo %d: r_fork locked\n", id);
```

### Valgrind para data races
```bash
valgrind --tool=helgrind ./philo 5 800 200 200
```

### Verificar leaks
```bash
valgrind --leak-check=full ./philo 5 800 200 200 7
```

### Teste de longa duração
```bash
./philo 5 800 200 200 &
PID=$!
sleep 60  # Roda por 1 minuto
kill $PID
```

---

## 🏆 Conclusão

O projeto Philosophers é uma excelente introdução a:
- Programação concorrente
- Sincronização de threads
- Problemas clássicos de concorrência
- Debugging de race conditions

Agora você tem uma implementação completa e corrigida! 🎉