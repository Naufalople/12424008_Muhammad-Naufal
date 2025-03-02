#include <iostream>
using namespace std;

struct barang
{
    string nama;
    int harga;
};
barang brg[100];

void menu(int &pilih){
    system("cls");
    cout << "----------------" << endl;
    cout << "      menu      " << endl;
    cout << "----------------" << endl;
    cout << "1. Input data   " << endl;
    cout << "2. sorting data " << endl;
    cout << "3. Pencarian    " << endl;
    cout << "4. Keluar       " << endl;
    cout << "----------------" << endl;
    cout << "pilih menu diatas : "; cin >> pilih;
}

void input(int &barangbanyak){
    system("cls");
    int tambah;
    cout << "Berapa banyak barang yang ingin ditambahkan? "; cin >> tambah;
    
    cin.ignore();

    for (int i = barangbanyak; i < barangbanyak + tambah; i++) {
        cout << "Barang ke-" << i+1 << endl;
        cout << "Nama barang: "; getline(cin, brg[i].nama);
        cout << "Harga barang: "; cin >> brg[i].harga;
        cin.ignore();
    }

    barangbanyak += tambah;
}

void bubble(int &barangbanyak){
    if (barangbanyak == 0)
    {
        cout << "data belum dimasukan" << endl;
    }
    else {
        system("cls");
        int i,j;
            for(i=0; i<barangbanyak-1; i++){
            for(j=i+1; j<barangbanyak; j++){
                if(brg[i].nama>brg[j].nama){
                    swap(brg[i],brg[j]);
                    }
            }
            }
        cout <<"\n\nData Setelah diurutkan:\n";
            for(i=0; i<barangbanyak; i++){
                cout << "barang ke-" << i+1 << endl;
                cout << "Nama barang : "<<brg[i].nama<< endl << "Harga barang : " << brg[i].harga << endl; 
                }
        cout <<"tekan enter untuk melanjutkan";
        cin.get();
        cin.get();
    }
}

void binary(int &barangbanyak){
    system("cls");
    if (barangbanyak == 0) {
        cout << "Data belum dimasukkan. Silakan input terlebih dahulu.\n";
        cout << "tekan enter untuk melanjutkan";
        cin.get();
        cin.get();
        return;
    }

    string x;
    bool found = false;
    int i = 0, j = barangbanyak - 1, t;

    cin.ignore();
    cout << "Barang yang dicari: "; 
    getline(cin, x);

    while (i <= j) {
        t = (i + j) / 2;
        if (brg[t].nama == x) {
            found = true;
            break;
        }
        else if (x < brg[t].nama) {
            j = t - 1;
        }
        else {
            i = t + 1;
        }
    }

    if (found)
        cout << "Barang ditemukan: " << brg[t].nama << " dengan harga " << brg[t].harga << endl;
    else{
        cout << "Barang tidak ditemukan dalam daftar." << endl;}
        cout << "tekan enter untuk melanjutkan";
        cin.get();
}

void sequential(int &barangbanyak){
    if (barangbanyak == 0) {
        cout << "Data belum dimasukkan. Silakan input terlebih dahulu.\n";
        cout << "tekan enter untuk melanjutkan";
        cin.get();
        cin.get();
        return;
    }
    int i,x; bool found;
    cout << "harga barang yang dicari = "; cin >> x;
    i=0; found=false;
    while ((i<barangbanyak) && (!found)){
        if (brg[i].harga==x)
            found = true;
        else
            i = i + 1;
  }
  if(found)
     cout<< "harga barang "  << x << " ditemukan dengan nama barang " <<brg[i].nama;
  else{
     cout << "barang dengan harga " << x << " tidak ditemuakn";
    }
    cout << "\ntekan enter untuk melanjutkan";
    cin.get();
    cin.get();
    }

void searching(int &barangbanyak){
    int cari;
    cout << "menu searching" << endl;
    cout << "1. Binary Search (nama)" << endl;
    cout << "2. Sequential Search (harga)" << endl;
    cout << "pilih nomor berapa : "; cin >> cari;
        if (cari == 1)
        {
            binary(barangbanyak);
        }
        else if (cari == 2)
        {
            sequential(barangbanyak);
        }
        else{
            cout << "menu tidak valid. silahkan coba lagi" << endl;
            cout << "tekan enter untuk melanjutkan";
            cin.get();
            cin.get();
        }
}

int main(){
    int pilih;
    int barangbanyak=0;
    while (true) {
    menu(pilih);
    if (pilih ==1 ){
        input(barangbanyak);
    }
    else if(pilih == 2){
        bubble(barangbanyak);
    }
    else if(pilih == 3){
        searching(barangbanyak);
    }
    else if(pilih == 4){
        cout << "keluar dari program";
        break;
    }
    else {
        cout << "input tidak valid. silahkan coba lagi \n";
        cout << "tekan enter untuk kembali ke menu";
        cin.get();
        cin.get();
    }
    }
}