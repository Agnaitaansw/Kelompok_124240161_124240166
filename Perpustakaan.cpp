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
    bool tersedia = true; 
    Buku* next;
};
// Struct anggota
struct anggota {
    int idAnggota;
    string namaAnggota;
    anggota* next;
};

// Struct Peminjaman
struct peminjaman {
    string namaAnggota;
    int idBuku;
    string judulBuku;
    peminjaman* next;
};

// Pointer
Buku* headBuku = nullptr;
peminjaman* front = nullptr;
peminjaman* rear = nullptr;

// Fungsi untuk menambah data buku
void tambahBuku(int id_Buku, string Judul, int thn_terbit, string pengarang) {
    Buku* baru = new Buku{id_Buku, Judul, thn_terbit, pengarang, true, nullptr};
    if (!headBuku)
        headBuku = baru;
    else {
        Buku* temp = headBuku;
        while (temp->next)
            temp = temp->next;
        temp->next = baru;
    }
}

// Fungsi untuk mengurutkan data buku berdasarkan tahun terbit
void mengurutkanBuku() {
    if (!headBuku || !headBuku->next) return;

    for (Buku* i = headBuku; i->next; i = i->next) {
        for (Buku* j = i->next; j; j = j->next) {
            if (i->thn_terbit > j->thn_terbit) {
                swap(i->id_buku, j->id_buku);
                swap(i->Judul, j->Judul);
                swap(i->thn_terbit, j->thn_terbit);
                swap(i->pengarang, j->pengarang);
                swap(i->tersedia, j->tersedia);
            }
        }
    }
}

// Fungsi untuk menampilkan daftar buku
void tampilkanBuku() {
    Buku* temp = headBuku;
    if (!temp) {
        cout << "\nTidak ada buku.\n";
        return;
    }

    cout << "-------------------------------------------------------------\n";
    cout << "| Id_buku |    Judul Buku     | Tahun |    Pengarang    | Status |\n";
    cout << "-------------------------------------------------------------\n";

    while (temp) {
        cout << "| " << setw(7) << temp->id_buku
             << " | " << setw(18) << temp->Judul
             << " | " << setw(5) << temp->thn_terbit
             << " | " << setw(15) << temp->pengarang
             << " | " << (temp->tersedia ? "Tersedia" : "Dipinjam") << " |\n";
        temp = temp->next;
    }
    cout << "-------------------------------------------------------------\n";
}

// Fungsi untuk mencari buku berdasarkan ID
Buku* cariBuku(int idBuku) {
    Buku* temp = headBuku;
    while (temp) {
        if (temp->id_buku == idBuku)
            return temp;
        temp = temp->next;
    }
    return nullptr;
}
