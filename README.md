#  ChromaSelect : Natural Selection Simulator

A **biological evolution simulator** built in C++ using the LIFAMI graphics library. Insects must camouflage themselves against a background to survive — you play the role of a predator hunting them down. Over generations, the population evolves toward the optimal color through natural selection.

---

##  How to Play

- **Move your mouse** to control the predator cursor (transparent circle)
- **Click** to "eat" any insects within your cursor's radius
- Caught insects disappear
- When all insects are dead, a **new generation** spawns — inheriting the average color of the longest-surviving insects
- Watch the population gradually blend into the background!

---

##  Biological Principles Simulated

| Principle | Implementation |
|---|---|
| **Natural Selection** | Best-camouflaged insects (color closest to background) survive longest |
| **Heredity** | New generation inherits the average color of the top survivors |
| **Mutation** | Each insect's color is slightly randomized around the reference color |

---

##  How It Works

### Key Structures

```cpp
Vec2       // 2D position of an insect
Color      // RGB color of an insect
insect     // position, color, birth time, lifespan
popInsect  // array of insects, target color, mutation range, background image
```

### Evolutionary Parameters

| Parameter | Value | Role |
|---|---|---|
| `NB_INSECTS` | 50 | Population size |
| `range` | 127 | Max mutation per RGB channel |
| `good` | (127, 127, 127) | Starting color (grey) |
| Selection threshold | 80% | Only top 20% most resistant reproduce |

### Each Generation Cycle
```
1. Track lifespan of each caught insect
2. When all insects are dead:
   → compute min/max lifespans
   → select insects above 80% of max lifespan
   → compute their average color
   → spawn new generation with that color ± random mutation
```

---

##  Build & Run

### Requirements
- C++ compiler (g++)
- [LIFAMI graphics library](https://perso.univ-lyon1.fr/thierry.excoffier/COURS/LIFAMI/)

### Compile
```bash
g++ -o chromaselect main.cpp -llifami
```

### Run
```bash
./chromaselect
```

---

##  Concepts Used

- Biological modelling (natural selection, heredity, mutation)
- RGB color averaging and random mutation
- Mouse interaction and collision detection
- Generational population management
- Operator overloading on color/vector structures

---

##  Project Structure

```
ChromaSelect/
├── src/
│   └── main.cpp            # Main source file
├── docs/
│   └── Markdown_ ChromaSelect.pdf         # Full project report (French)
└── README.md
```

---

## 🎓Academic Context

Developed as part of the **LIFAMI** course (C++ graphics programming) at **Université Claude Bernard Lyon 1** — Licence Mathématiques-Informatique, Year 1 (2025).
