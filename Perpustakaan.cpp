#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

// Struct Buku
struct Buku {
    int id_buku;
    string Judul;
    int thn_terbit;
    string pengarang;
    bool tersedia = true; // Tambahan atribut tersedia
    Buku* next;
};
