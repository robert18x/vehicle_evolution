# Vehicle Evolution

Projekt polega na symulacji poruszających się pojazdów i ewolucji ich kształu, pod kryterium przemieszczenia się jak najdalej w jak najkrótszym odcinku czasu.

# Wykorzystywane narzędzia w projekcie
Projekt jest napisany w języku C++. Do budowy projektu jest wykorzystane narzędzie CMake z zintegrowanym menażdżerem pakietów conan. Główymi wykorzystywanymi bibliotekami są [box2d](https://github.com/erincatto/box2d) oraz [dear imgui](https://github.com/ocornut/imgui). Do testów jest wykorzystywana biblioteka [googletest](https://github.com/google/googletest). 

## Instalacja i uruchomienie
### Ubuntu 20.04
Po pobraniu źródeł będąc w głównym katalogu projektu należy uruchomić skrypty:
 - `scripts/ubuntu_prepare_environment.sh` - skrypt przygotowujący środowisko
 - `scripts/ubuntu_build_debug.sh` - skrypt budujący projekt w trybie Debug

Po zbudowaniu projektu w katalogu `build/src/` będzie znajdować się plik wykonywalny programu o nazwie `vehicle_evolution`, a w katalogu `build/test/` plik wykonywalny testów o nazwie `vehicle_evolution_test`.

Dodatkowo po zbudowaniu projektu w katalogu `build/doxygen` będzie znajdować się wygenerowana dokumentacja. Aby ją włączyć należy otworzyć plik `html/index.html`.

## Windows 10
Należy zainstalować w najnowszej wersji następujące narzędzia:
 * cmake
 * python, a poprzez python-a paczkę conan
 * visual studio 2022 -> kompilator MSVC
 * ...

Następnie należy zbudować projekt cmake-owy w konsoli PowerShell (lub cmd, lecz w PS automatycznie są pobierane zmienne środowiskowe)


# Warning-i podczas budowania projektu
Projekt korzysta z zewnętrznych bibliotek i plików źródłowych. Niektóre z nich (np. imgui) generuje bardzo dużą ilość ostrzeżeń. Sam kod źródłowy projektu `Vehicle Evolution` nie generuje ostrzeżeń ani błędów.
