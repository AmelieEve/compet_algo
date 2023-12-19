#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class union_find {
private:
    vector<int> id; // id[i] = parent of i
    vector<int> sz; // sz[i] = number of objects in subtree rooted at i
    int count; // number of components
public:
    union_find(int N) : id(N, 0), sz(N, 1) {
        count = N;
        for (int i = 0; i < N; i++) {
            id[i] = i;
        }
    }
    int nb_components() {
        return count;
    }
    int size_set(int i) {
        return sz[find_set(i)];
    }
    int find_set(int i) {
        return (id[i] == i) ? i : (id[i] = find_set(id[i]));
    }
    bool connected(int i, int j) {
        return find_set(i) == find_set(j);
    }
    void union_set(int p, int q) {
        int i = find_set(p);
        int j = find_set(q);
        if (i == j) return;
        // make smaller root point to larger one
        if (sz[i] < sz[j]) { id[i] = j; sz[j] += sz[i]; }
        else               { id[j] = i; sz[i] += sz[j]; }
        count--;
    }
};

template <typename T>
class segment_tree {
    struct node {
        T sum = T{};
        T min = std::numeric_limits<T>::max();
        int from = 0;
        int to = -1;
        bool pending = false;
        T pending_val;
        int size() const {
            return to - from + 1;
        }
    };
    std::vector<node> heap;
    std::vector<T>  array;
    int heap_size;
    int array_size;
    int left (int p) { return p << 1; }
    int right(int p) { return (p << 1) + 1; }
    bool contains(int from1, int to1, int from2, int to2) {
        return from1 <= from2 && to2 <= to1;
    }
    bool intersects(int from1, int to1, int from2, int to2) {
        return (from1 <= from2 && to1 >= from2) ||
            (from1 >= from2 && from1 <= to2);
    }
public:
    segment_tree(const std::vector<T>& array) {
        this->array = array;
        array_size = array.size();
        heap_size = 2 * (1 << ((int)log2(array.size()) + 1));
        heap.resize(heap_size);
        build(1, 0, array_size - 1);
    }
    segment_tree(int n) : array(n) {
        array_size = array.size();
        heap_size = 2 * (1 << ((int)log2(array.size()) + 1));
        heap.resize(heap_size);
        build(1, 0, array_size - 1);
    }

private:
    void build(int heap_index, int from, int to) {
        node& n = heap[heap_index];
        n.from = from;
        n.to = to;
        if (from == to) {
            n.sum = array[from];
            n.min = array[from];
        } else {
            int middle = from + (to - from) / 2;
            build(left(heap_index), from, middle);
            build(right(heap_index), middle + 1, to);
            n.sum = heap[left(heap_index)].sum + heap[right(heap_index)].sum;
            n.min = std::min(heap[left(heap_index)].min, heap[right(heap_index)].min);
        }
    }
public:
    T get_sum(int from, int to) {
        return get_sum(1, from, to);
    }
private:
    T get_sum(int heap_index, int from, int to) {
        node& n = heap[heap_index];
        if (n.pending && contains(n.from, n.to, from, to)) {
            return (to - from + 1) * n.pending_val;
        }
        if (contains(from, to, n.from, n.to)) {
            return n.sum;
        }
        if (intersects(from, to, n.from, n.to)) {
            propagate(heap_index);
            return get_sum(left(heap_index), from, to) + get_sum(right(heap_index), from, to);
        }
        return T{};
    }
public:
    T get_min(int from, int to) {
        return get_min(1, from, to);
    }
private:
    T get_min(int heap_index, int from, int to) {
        node& n = heap[heap_index];
        if (n.pending && contains(n.from, n.to, from, to)) {
            return n.pending_val;
        }
        if (contains(from, to, n.from, n.to)) {
            return n.min;
        }
        if (intersects(from, to, n.from, n.to)) {
            propagate(heap_index);
            return std::min(get_min(left(heap_index), from, to), get_min(right(heap_index), from, to));
        }
        return std::numeric_limits<T>::max();
    }
public:
    void update(int from, int to, T value) {
        update(1, from, to, value);
    }
private:
    void update(int heap_index, int from, int to, T value) {
        node& n = heap[heap_index];
        if (contains(from, to, n.from, n.to)) {
            change(n, value);
        }
        else if (intersects(from, to, n.from, n.to)) {
            propagate(heap_index);
            update(left(heap_index), from, to, value);
            update(right(heap_index), from, to, value);
            n.sum = heap[left(heap_index)].sum + heap[right(heap_index)].sum;
            n.min = std::min(heap[left(heap_index)].min, heap[right(heap_index)].min);
        }
    }
    void propagate(int heap_index) {
        node& n = heap[heap_index];
        if (n.pending) {
            if (n.size() != 1) {
                change(heap[left(heap_index)], n.pending_val);
                change(heap[right(heap_index)], n.pending_val);
            }
            n.pending = false;
        }
    }
    void change(node& n, int value) {
        n.pending = true;
        n.pending_val = value;
        n.sum = n.size() * value;
        n.min = value;
        array[n.from] = value;
    }
};

/*
  Problème 1.
  Énoncé : On voudrait savoir si toutes les lettres d'un mot sont dans un autre mot et vice-versa. Par exemple, pour "pascalgarcia", on retrouve bien toutes les lettres dans "lascarpacagi" et vice-versa mais aussi
          dans "lscarpgi".
             
  Entrée : On vous donne un premier mot 'm1', d'au plus 10^5 caractères, et un deuxième mot 'm2' d'au plus 10^5 caractères.
  Sortie : Afficher 'OUI' si on retrouve bien toutes les lettres du premier mot dans le deuxième mot et vice-versa et 'NON' sinon.

  Exemples :
   Entrée : toto 
            titi 
   Sortie : NON

   Entrée : lalala 
            aaaaaal
   Sortie : OUI

   Entrée : laaaaaaa 
            al
   Sortie : OUI

*/
void problem1() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string w1, w2;
    cin >> w1 >> w2;
    set<char> s1{ begin(w1), end(w1) };
    set<char> s2{ begin(w2), end(w2) };
    cout << (s1 == s2 ? "OUI" : "NON") << '\n';
    cout.flush();
}

/*
  Problème 2.
  Énoncé : Nous nous situons dans un monde en grille de dimension n x n. Un exemple de monde est donné ci-dessous.

    -- j -->
    |     0   1   2   3   4   5   6   7
    i   +---+---+---+---+---+---+---+---+
    | 0 |   |   |   |   |   |   |   |   |
    v   +---+---+---+---+---+---+---+---+
      1 |   | A |   |   | # | # | # | # |
        +---+---+---+---+---+---+---+---+
      2 |   |   |   |   | # |   |   |   |
        +---+---+---+---+---+---+---+---+
      3 |   |   | # | # | # |   |   |   |
        +---+---+---+---+---+---+---+---+
      4 |   |   |   |   | # |   |   |   |
        +---+---+---+---+---+---+---+---+
      5 |   |   |   |   | # |   |   |   |
        +---+---+---+---+---+---+---+---+
      6 |   |   |   |   | # |   |   |   |
        +---+---+---+---+---+---+---+---+
      7 |   |   |   |   |   |   |   |   |
        +---+---+---+---+---+---+---+---+

    Dans cette grille, le 'A' représente l'agent et les '#' des murs. Il peut y avoir plusieurs murs, mais il y a un et un seul agent.
    L'agent peut se déplacer d'une et une seule case dans une des quatre directions : haut, bas, gauche et droite. Si l'agent se déplace dans un mur, il reste sur la case où il se trouvait et il ne peut
    effectuer l'action suivante. Si l'agent se déplace en dehors de la grille, il reste sur la case où il se trouvait, mais ne pourra plus bouger de cette case.    
    On vous donne la case de départ de l'agent et la suite des actions de l'agent et votre objectif est de déterminer la case d'arrivée. 

  Entrée : un entier 'n' donnant la dimension de la grille avec 2 <= n <= 1000. Ensuite n lignes contenant chacune n caractères décrivant la grille. Une case vide sera représentée par un point ('.'). 
          Ensuite un entier 'm' donnant le nombre d'actions avec 1 <= m <= 10000. Enfin, les m actions, une action est représentée par un caractère : 
           * 'g' pour gauche
           * 'd' pour droite
           * 'h' pour haut
           * 'b' pour bas
           
  Sortie : Les coordonnées de la case d'arrivée. On affichera d'abord i puis j.

  Exemple :
   Entrée : 8
            ........
            .A..####
            ....#...
            ..###...
            ....#...
            ....#...
            ....#...
            ........
            12
            d d d g h h h g g b b b
   Sortie : 0 3
*/

void problem2() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    pair<int,int> pos_agent;
    vector<vector<char>> grid(n, vector<char>(n));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if(grid[i][j] == 'A') {
                pos_agent = {i,j};
            }
        }
    }

    int m;
    cin >> m;

    // Possible moves
    map<char,pair<int,int>> string2delta { {'h',{-1, 0}}, {'b',{1, 0}}, {'g',{0, -1}}, {'d',{0,1}}};

    pair<int,int> next_pos;
    bool skip = false;
    for(int a = 0; a < m; a++) {
        char action;
        cin >> action;
        if(skip) {
            cin >> action;
            skip = false;
        }
        next_pos.first = pos_agent.first + string2delta[action].first;
        next_pos.second = pos_agent.second + string2delta[action].second;
        if(next_pos.first < 0 || next_pos.first > n || next_pos.second < 0 || next_pos.second > n) {
            break;
        }
        if(grid[next_pos.first][next_pos.second] != '#') {
            pos_agent = next_pos;
        } else {
            skip = true;
        }
    }
    cout << pos_agent.first << " " << pos_agent.second << endl;

    cout.flush();
}

/*
Problème 3.
Énoncé : Dans le jeu 'Risk world domination' on peut utiliser l'option 'blizzard' qui permet de rendre inaccessible un ou plusieurs pays sur la carte du jeu. 
        Pour que le blizzard soit intéressant, il faut que tous les pays puissent encore être accessibles à partir de n'importe quels autres. On va représenter
        la carte par un graphe non orienté où les pays seront des entiers. On pourrait avoir le graphe suivant par exemple :
          0 --> [1, 2]
          1 --> [0]
          2 --> [0]
        dans ce graphe, 0 est connecté à 1 et 2, 1 à 0 et 2 à 0.
        On va ensuite indiquer les pays qui sont des blizzards en donnant leurs numéros. Par exemple :
          2
        Ici, pour tous les pays qui ne sont pas des blizzards, on peut trouver au moins un chemin entre chacun d'entre eux. On supposera que tous les pays ne sont pas des blizzards.
        Votre objectif est d'afficher 'OUI' si tous les pays qui ne sont pas des blizzards peuvent s'atteindre mutuellement et 'NON' sinon.

  Entrée : un entier 'n' représentant le nombre de pays sur la carte, 1 <= n <= 100000 (les pays vont de 0 à n - 1). Ensuite un entier 'm' donnant le nombre d'arrêtes,
          puis la description des arrêtes (ne pas oublier que le graphe est non orienté). Ensuite un entier 'k' décrivant le nombre de blizzards et k entiers représentant les pays où il y a du blizzard.
  Sortie : 'OUI' si les pays qui ne sont pas des blizzards peuvent s'atteindre mutuellement par au moins un chemin et 'NON' sinon.

  Exemple :
   Entrée : 3
            2
            0 1
            0 2
            1
            2
   Sortie : OUI
*/

void problem3() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<pair<int,int>> aretes;
    for(int i = 0; i < m; i++) {
        int pays1, pays2;
        cin >> pays1 >> pays2;
        aretes.push_back({pays1, pays2});
    }

    int k;
    cin >> k;
    vector<int> blizzards(k);
    for(int i = 0; i < k; i++) {
        cin >> blizzards[i];
    }

    auto uf = union_find(n);
    for(auto [pays1, pays2] : aretes) {
        if(find(blizzards.begin(), blizzards.end(), pays1) == blizzards.end() && find(blizzards.begin(), blizzards.end(), pays2) == blizzards.end()) {
            uf.union_set(pays1, pays2);
        }
    }
    int nb_comp = uf.nb_components();

    if(nb_comp > k+1) {
        cout << "NON" << endl;
    } else {
        cout << "OUI" << endl;
    }

    cout.flush();
}

/*
  Problème 4.
  Énoncé : Nous nous situons dans un monde en grille de dimension n x n. Un exemple de monde est donné ci-dessous.

    +---+---+---+---+---+---+---+---+
    |   |   |   |   |   |   |   |   |
    +---+---+---+---+---+---+---+---+
    |   | A |   |   | # | # | # | # |
    +---+---+---+---+---+---+---+---+
    |   |   |   |   | # | X |   |   |
    +---+---+---+---+---+---+---+---+
    |   |   | # | # | # |   |   |   |
    +---+---+---+---+---+---+---+---+
    |   |   |   |   | # |   |   |   |
    +---+---+---+---+---+---+---+---+
    |   |   |   |   | # |   |   |   |
    +---+---+---+---+---+---+---+---+
    |   |   |   |   | # |   |   |   |
    +---+---+---+---+---+---+---+---+
    |   |   |   |   |   |   |   |   |
    +---+---+---+---+---+---+---+---+

    Dans cette grille, le 'A' représente l'agent, le 'X' le but, et les '#' des murs. Il peut y avoir plusieurs murs, mais il y a un et un seul agent et au plus un but.
    L'agent peut se déplacer dans une des quatre directions : haut, bas, gauche et droit. Mais il possède un super pouvoir, qu'il ne peut utiliser qu'un certain nombre de fois (un des paramètres du problème),
    qui lui permet de se déplacer dans un mur (la case où il arrive après un déplacement est un mur). L'objectif de l'agent est d'atteindre le but en dépensant le moins d'énergie possible, sachant qu'un déplacement 
    dans une des quatre directions lui coûte une unité, et le passage au travers d'un mur lui coûte 'c' unités (un autre paramètre du problème) au lieu d'une unité. L'agent ne peut pas sortir de la grille.
    Pour une grille donnée vous devez indiquer le coût minimal nécessaire à l'agent pour atteindre le but. Si ce n'est pas possible, vous afficherez la valeur -1. 

  Entrée : 'n' la dimension de la grille avec 2 <= n <= 1000. Ensuite n lignes contenant chacune n caractères décrivant la grille. Une case vide sera représentée par un point ('.'). Ensuite le nombre 'k' d'utilisation
          possible du super pouvoir avec 0 <= k <= 100, puis le coût 'c' du super pouvoir, avec 0 <= c <= 1e5.
  Sortie : Le coût minimal pour atteindre le but ou -1 si ce n'est pas possible.

  Exemples :
   Entrée : 8
            ........
            .A..####
            ....#X..
            ..###...
            ....#...
            ....#...
            ....#...
            ........
            1
            1

   Sortie : 5

   Entrée : 8
            ........
            .A..####
            ....#X..
            ..###...
            ....#...
            ....#...
            ....#...
            ........
            10
            100

   Sortie : 15

   Entrée : 5
            ....A
            #####
            #####
            ..X..
            .....
            1
            1

   Sortie : -1

   Entrée : 5
            ....A
            #####
            #####
            ..X..
            .....
            2
            4

   Sortie : 11
   
*/
void problem4() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    using pii = pair<int, int>;
    struct node {
        int i;
        int j;
        int super_power;
        int cost;
        node(int i = 0, int j = 0, int sup = 0, int c = 0) : i{i}, j{j}, super_power{sup}, cost{c} {}
        bool operator>(const node& n) const {
            return cost > n.cost;
        }
    };
    int n;
    cin >> n;
    vector<string> grid(n);
    int ai, aj;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'A') ai = i, aj = j;
        }
    }
    int nsup;
    cin >> nsup;
    int csup;
    cin >> csup;
    auto possible = [&](int i, int j) {
        return i >= 0 && i < n && j >= 0 && j < n;
    };
    auto dijkstra = [&] {
        set<tuple<int, int, int>> visited;
        priority_queue<node, vector<node>, greater<node>> q;
        q.emplace(ai, aj, nsup, 0);
        while (!q.empty()) {
            auto [i, j, sup_left, cost] = q.top(); q.pop();
            if (grid[i][j] == 'X') return cost;
            if (visited.count({i, j, sup_left})) continue;
            visited.emplace(i, j, sup_left);
            for (pii delta : vector<pii>{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}) {
                int ii = i + delta.first;
                int jj = j + delta.second;
                if (!possible(ii, jj)) continue;
                if (grid[ii][jj] == '#') {
                    if (sup_left == 0) continue;
                    q.emplace(ii, jj, sup_left - 1, cost + csup);
                } else {
                    q.emplace(ii, jj, sup_left, cost + 1);
                }
            }
        }
        return -1;
    };
    cout << dijkstra() << '\n';
    cout.flush();
}

/*
  Problème 5.
  Énoncé : On dispose de plusieurs colonnes de béton alignées. On voudrait pouvoir tailler un carré de côté de longueur 'l' avec l la plus grande valeur possible dans cette rangée de colonnes. 
          Pour ce faire, on a besoin de trouver un segment de colonnes de longueur l pour lequel la hauteur minimale des colonnes est de hauteur l. Par exemple :

                  +-+
              +-+-+ |
          +-+ | | | |
          | +-+ | | |
    ______| | | | | |______

          l = 3 est la réponse pour la configuration ci-dessus en utilisant les 3 dernières colonnes (base de longueur 3 et la hauteur de chaque colonne >= 3). 

  Entrée : le nombre 'n' de colonnes, avec 1 <= n <= 10^5 puis n entiers représentant la hauteur h de chaque colonne, la hauteur 1 <= h <= 10^9.

  Sortie : la longueur maximale du carré que l'on peut construire.

  Exemple :
   Entrée : 5
            2 1 3 3 4
   Sortie : 3
*/
void problem5() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int> heights(n);
    for(auto& h : heights) cin >> h;
    segment_tree<int> st(heights);
    auto possible = [&](int l) -> bool {
        for (int i = 0; i + l <= n; i++) {
            if (st.get_min(i, i + l - 1) >= l) return true;
        }
        return false;
    };
    int lo = 1, hi = n;
    int l = 1;
    while (lo <= hi) {
        int m = lo + (hi - lo) / 2;
        if (possible(m)) {
            l = m;
            lo = m + 1;
        } else {
            hi = m - 1;
        }
    }
    cout << l << '\n';
    cout.flush();
}

/*
  Problème 6.
  Énoncé : On vous donne une chaîne de caractères 'S' contenant 64 caractères. Les caractères sont des '0' ou des '1'. 
          On vous donne ensuite une autre chaîne 'P' de caractères de 4 caractères représentant un motif lui aussi constitué
          de '0' ou de '1'. 
          On vous donne ensuite un entier 'N' et on va créer une nouvelle chaîne à partir de 'S' qui est la concaténation de N fois la chaîne S.
          Vous devez compter combien de fois vous trouvez le motif entre les positions :
          [0..3], [4..7], [8..11], ... de cette nouvelle chaîne

  Entrée : la chaîne de 64 caractères, puis la chaîne de 4 caractères, puis l'entier 'N', avec 1 <= N <= 10^9.
  Sortie : le nombre de fois où l'on trouve le motif.

  Exemples :
   Entrée : 0000101011110000111110101111000011110000111100001010111100001010
            1010
            100
   Sortie : 400
*/
void problem6() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, p;
    cin >> s >> p;
    int n;
    cin >> n;

    int count = 0;
    for(int chunk = 0; chunk < 16; chunk++) {
        string chunk_s = s.substr(4*chunk, 4);
        if(p.compare(chunk_s) == 0) {
            count++;
        }
    }

    cout << count*n << endl;

    cout.flush();
}

/*
  Problème 7.
  Énoncé : Cet énoncé est vaguement inspiré du jeu 'Risk World Domination'.
        Des troupes vont s'affronter dans deux scénarios différents :
            1. Nos troupes contre des troupes ennemies.
            2. Nos troupes pour prendre une capitale défendue par des troupes ennemies.
        Les soldats s'affrontent un par un, à tour de rôle, le gagnant pouvant encore combattre et le perdant disparaît.

        Dans le scénario 1., quand notre soldat affronte un soldat ennemi, il a une probabilité 'p_bigger' de gagner si la taille de son armée est 
        strictement supérieure à celle de son adversaire, et une probabilité 'p_smaller' sinon. Notons que notre adversaire à respectivement une probabilité
        (1 - 'p_bigger') de gagner et (1 - 'p_smaller').
        
        Dans le scénario 2., lorsque l'on attaque une capitale, quand notre soldat affronte un soldat ennemi, il a une probabilité 'p_two_times' de gagner si
        la taille de son armée est strictement 2 fois plus grande que l'armée de la capitale et 'p_less_two_times' sinon.
        
        Notons que les probabilités vont évoluées durant la bataille suivant la taille des armées respectives.

        Votre mission est d'indiquer pour une taille donnée de notre armée et de l'armée adverse, et un mode de combat (capitale ou normal), par 'OUI', si notre 
        armée a une probabilité de gagner la bataille > 0.5 et 'NON' sinon.

  Entrée : La probabilité 'p_bigger', puis 'p_smaller', puis la probabilité 'p_two_times' puis 'p_less_two_times'. Ensuite 'M', la taille maximale des deux armées. On aura 1 <= M <= 100.
           Ensuite, un nombre 'Q', avec 1 <= Q <= 10000 indiquant le nombre de scénarios.
           Ensuite Q lignes avec pour chacune, la taille de l'armée adverse, puis la taille de notre armée, puis le mode (une chaine de caractères) : 'normal' ou 'capital'.

  Sortie : 'OUI' si la probabilité pour notre armée de gagner la bataille est strictement supérieure à 0.5 et 'NON' sinon.

  Exemple :
   Entrée : 1 1 1 1
            20
            4
            20 1 normal
            20 1 capital
            1 20 normal
            1 20 capital
   Sortie : OUI
            OUI
            OUI
            OUI
*/
void problem7() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // TO DO
    cout.flush();
}

/*
  Problème 8.
  Énoncé : Nous avons reçu pour Noël un jeu qui va sûrement devenir très populaire. Il y a 'n' cases alignées numérotées de 0 à (n - 1).
          On doit essayer d'atteindre la case (n - 1) à partir de la case 0. Sur chaque case il y a un entier. Lorsque l'on se trouve
          sur une case 'i', on peut sauter en avant de 'p' cases en utilisant un diviseur premier p de i. Sauter de p cases compte alors pour un coup. 
          Vous devez essayer d'atteindre la case (n - 1) en le moins de coups possibles.

  Entrée : Un entier 'n', le nombre de cases avec 1 <= n <= 10^5. Ensuite n entiers représentant les nombres 'i' sur chacune des cases. On aura 1 <= i <= 10^9. 

  Sortie : Le nombre de coups minimal pour passer de la case 0 à la case (n - 1) et -1 si ce n'est pas possible.

  Exemple :
   Entrée : 11
            2 8 21 5 5 5 5 5 5 5 5
   Sortie : 3
*/
void problem8() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // TO DO
    cout.flush();
}

/*
  Problème 9.
  Énoncé: Il y a 'n' arbres plantés en ligne droite. Les arbres sont numérotés de 0 à (n - 1). Malheureusement, certains arbres ont pris feu.
          On supposera que les arbres 0 et (n - 1) auront toujours pris feu dans les différents tests (ils seront toujours présents dans la liste initiale des
          arbres aillant pris feu). On peut protéger à chaque pas de temps un et un seul arbre qui n'est pas en feu. Le feu va se propager à chaque pas de temps
          à l'arbre ou aux deux arbres qui lui sont voisins si ceux-ci ne sont pas protégés.
          Votre mission est de protéger un maximum d'arbres. Notons que vous commencez par protéger un arbre, puis le feu se propage et ainsi de suite.

  Entrée : Un entier 'n' représentant le nombre d'arbres avec 2 <= n <= 10^5. Ensuite un entier 'm' indiquant le nombre d'arbres initialement en feu avec 2 <= m <= n.
           Ensuite m entiers indiquant les arbres initialement en feu.

  Sortie : Le nombre d'arbres que vous avez réussi à sauver.

  Exemple :
   Entrée : 11
            3
            0 4 10
   Sortie : 4
*/
void problem9() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // TO DO
    cout.flush();
}

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string problem{argv[1]};
    if (problem == "problem1") {
        problem1();
    }
    if (problem == "problem2") {
        problem2();
    }
    if (problem == "problem3") {
        problem3();
    }    
    if (problem == "problem4") {
        problem4();
    }
    if (problem == "problem5") {
        problem5();
    }    
    if (problem == "problem6") {
        problem6();
    }
    if (problem == "problem7") {
        problem7();
    }
    if (problem == "problem8") {
        problem8();
    }
    if (problem == "problem9") {
        problem9();
    }
}