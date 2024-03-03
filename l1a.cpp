#include <iostream>

int main(void) {
    int P, V, Q, M;
    std::cin >> P >> V;
    std::cin >> Q >> M;

    int start_vas = P - V;
    int end_vas = P + V;
    int start_mas = Q - M;
    int end_mas = Q + M;

    int start_cover = std::max(start_vas, start_mas);
    int end_cover = std::min(end_vas, end_mas);

    int cover = 0;
    if (start_cover <= end_cover) {
        cover = end_cover - start_cover + 1;
    }

    int result = (end_vas - start_vas + 1) + (end_mas - start_mas + 1) - cover;
    std::cout << result;
}