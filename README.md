# Big-numbers
Big numbers
Problem A – Duże liczby
Zadanie
Napisz program podający wyniki operacji arytmetycznych dla dużych liczb całkowitych
dodatnich. Należy uwzględnić 4 podstawowe operacje: dodawanie (+), odejmowanie (-),
mnożenie (*) i dzielenie całkowite (/).
Wejście
Pierwszy wiersz standardowego wejścia zawiera jedną liczbę całkowitą Z (1 ≤ Z ≤ 200)
określającą liczbę testów zdefiniowanych w kolejnych wierszach. Każdy test zajmuje jeden
wiersz standardowego wejścia i zawiera zapis jednego działania arytmetycznego, tzn. dwa
ciągi cyfr rozdzielone operatorem działania (bez dodatkowych spacji). Ciągi cyfr liczą nie
więcej niż 256 znaków.
Wyjście
Dla każdego testu odpowiedź powinna pojawić się w osobnym wierszu standardowego
wyjścia. Powinna ona zawierać ciąg cyfr reprezentujący liczbę będącą wynikiem danego
działania. Jeśli wynik działania jest ujemny, wynikowy ciąg cyfr powinien być poprzedzony
znakiem ‘-‘.
Przykład
Dla danych:
4
12345678901234567890+98765432109876543210
12345678901234567890*98765432109876543210
12345678901234567890-98765432109876543210
98765432109876543210/12345678901234567890
prawidłową odpowiedzią jest:
111111111011111111100
1219326311370217952237463801111263526900
-86419753208641975320
8
