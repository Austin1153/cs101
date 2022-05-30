#include <iostream>

using namespace std;

class MMmanger {
  private:
    int num_of_space;
    int id;
    int *g_mm;

  public:
    MMmanger(int size) {
      num_of_space = size;
      id = 0;
      g_mm = (int *)calloc(size, sizeof(int));
    }
    ~MMmanger() { free(g_mm); }
    int *calloc_MM(int size) {
      int indx = -1;
      for (int i = 0; indx < 0 && i < num_of_space; i++) {
        int j = 0;
        for (int k = 0; !j && k < size; k++) {
          if (g_mm[i + k] != 0 || i + k >= num_of_space) j = 1;
        };
        if (!j) indx = i;
      };
      if (indx >= 0) {
        for (int i = 0; i < size; i++) g_mm[indx + i] = id + 1;
        id++;
      };
      print_calloc_array(indx, size);
      return indx >= 0 ? &g_mm[indx + size - 1] : NULL;
    }
    void free_MM(int *p) {
      for (int i = 0; i < num_of_space; i++) if (g_mm[i] == *p) g_mm[i] = 0;
      print_calloc_array(0, 0);
    }
    int get_MMCapacity() {
      int capacity = 0;
      for (int i = 0; i < num_of_space; i++) if (g_mm[i] == 0) capacity++;
      return capacity;
    }
    void print_calloc_array(int flag, int size) {
      cout << "Capacity:" << get_MMCapacity() << " - ";
      for (int i = 0; i < num_of_space; i++) g_mm[i] ? cout << "1" : cout << "0";
      if (flag < 0) cout << " <- Out of space: demand " << size;
      cout << endl;
    }
};

int main() {
  MMmanger mmer(10);
  int *p1 = mmer.calloc_MM(1);
  int *p2 = mmer.calloc_MM(2);
  int *p3 = mmer.calloc_MM(3);
  int *p4 = mmer.calloc_MM(4);
  mmer.free_MM(p1);
  mmer.free_MM(p4);
  int *p5 = mmer.calloc_MM(6);

  return 0;
}
