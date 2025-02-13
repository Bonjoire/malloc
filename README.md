# MALLOC
Ce projet est une réimplémentation de la fonction malloc en C. L’objectif est d’acquérir une compréhension approfondie de la gestion dynamique de la mémoire.

## 💻 Installation

```sh
git clone git@github.com:Bonjoire/malloc.git
cd malloc
```

Créer la librairie partagée libft_malloc.so:
```sh
make
```

Tester le main:
```sh
make test
```

### Liste des fonctions implémentées:

```sh
void	*malloc(size_t size);
void	free(void *ptr);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem();
void	show_alloc_debug();
void    show_hexa_dump();
```

## 📝 Fonctionnalités

- Allocation dynamique de mémoire
- Gestion des blocs libres (défragmentation)
- Alignement de la mémoire
- Support multi-thread
- Affichage en hexadécimal

## ⚙️ Comment ça fonctionne ?

<!-- - 1️⃣ **Ouvrir le fichier objet**  
- 2️⃣ **Mapper le fichier en mémoire**  
- 3️⃣ **Lire le header ELF** (<u>en-tête contenant des infos sur le fichier, ex: type 32 bits ou 64 bits</u>)  
- 4️⃣ **Lire la table des sections**  
- 5️⃣ **Lire la table des symboles**  
- 6️⃣ **Interpréter et afficher les symboles**  -->

## 🔗 Ressources

- [Data structure alignment](https://en.wikipedia.org/wiki/Data_structure_alignment)
- [Memory mapping video](https://www.youtube.com/watch?v=8hVLcyBkSXY)
- [Defragmentation](https://en.wikipedia.org/wiki/Defragmentation)
- [Hex_dump](https://en.wikipedia.org/wiki/Hex_dump)
