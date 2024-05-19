#include <iostream>
#include <fstream>
#include <chrono>
#include <random>

using namespace std;

 int int_val1, int_val2;
float float_val1, float_val2;
float int_result, float_result;


void generateData();
pair<float, float> addInt();
pair<float, float> subInt();
pair<float, float> mulInt();
pair<float, float> divInt();
pair<float, float> addFloat();
pair<float, float> subFloat();
pair<float, float> mulFloat();
pair<float, float> divFloat();
void test();

int main() {
    generateData();
    test();
    return 0;
}

void generateData(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> int_dist(1, 1000);
    std::uniform_real_distribution<float> float_dist(-1000000000.0, 1000000000.0);

    int_val1 = int_dist(gen);
    int_val2 = int_dist(gen);
    float_val1 = float_dist(gen);
    float_val2 = float_dist(gen);
}

void test(){
    float total_intAdd_duration,total_intSub_duration,total_intMul_duration,total_intDiv_duration,total_intAdd_asm_duration,total_intSub_asm_duration,total_intMul_asm_duration,total_intDiv_asm_duration, total_floatAdd_duration, total_floatSub_duration, total_floatMul_duration, total_floatDiv_duration, total_floatAdd_asm_duration, total_floatSub_asm_duration, total_floatMul_asm_duration, total_floatDiv_asm_duration;

    for (int i = 0; i < 1; i++) {
        auto durations_add = addInt();
        auto durations_sub = subInt();
        auto durations_mul = mulInt();
        auto durations_div = divInt();
        total_intAdd_duration += durations_add.first;
        total_intSub_duration += durations_sub.first;
        total_intMul_duration += durations_mul.first;
        total_intDiv_duration += durations_div.first;
        total_intAdd_asm_duration += durations_add.second;
        total_intSub_asm_duration += durations_sub.second;
        total_intMul_asm_duration += durations_mul.second;
        total_intDiv_asm_duration += durations_div.second;
        auto durations_float_add = addFloat();
        auto durations_float_sub = subFloat();
        auto durations_float_mul = mulFloat();
        auto durations_float_div = divFloat();
        total_floatAdd_duration += durations_float_add.first;
        total_floatSub_duration += durations_float_sub.first;
        total_floatMul_duration += durations_float_mul.first;
        total_floatDiv_duration += durations_float_div.first;
        total_floatAdd_asm_duration += durations_float_add.second;
        total_floatSub_asm_duration += durations_float_sub.second;
        total_floatMul_asm_duration += durations_float_mul.second;
        total_floatDiv_asm_duration += durations_float_div.second;


    }

    ofstream file("Result.txt", ios::app);
    file<<"Typ liczb: int"<<endl;
    file << "Sredni czas dla operacji dodawania: " << total_intAdd_duration / 10 << " nanoseconds" << endl;
    file << "Sredni czas dla operacji odejmowania: " << total_intSub_duration / 10 << " nanoseconds" << endl;
    file << "Sredni czas dla operacji mnożenia: " << total_intMul_duration / 10 << " nanoseconds" << endl;
    file << "Sredni czas dla operacji dzielenia: " << total_intDiv_duration / 10 << " nanoseconds" << endl;
    file << "Sredni czas dla operacji dodawania w asm: " << total_intAdd_asm_duration / 10 << " nanoseconds" << endl;
    file << "Sredni czas dla operacji odejmowania w asm: " << total_intSub_asm_duration / 10 << " nanoseconds" << endl;
    file << "Sredni czas dla operacji mnożenia w asm: " << total_intMul_asm_duration / 10 << " nanoseconds" << endl;
    file << "Sredni czas dla operacji dzielenia w asm: " << total_intDiv_asm_duration / 10 << " nanoseconds" << endl;
    file<<endl<<endl;

    file << "Typ liczb: float" << endl;
    file << "Sredni czas dla operacji dodawania: " << total_floatAdd_duration / 10 << " nanoseconds" << endl;
    file << "Sredni czas dla operacji odejmowania: " << total_floatSub_duration / 10 << " nanoseconds" << endl;
    file << "Sredni czas dla operacji mnożenia: " << total_floatMul_duration / 10 << " nanoseconds" << endl;
    file << "Sredni czas dla operacji dzielenia: " << total_floatDiv_duration / 10 << " nanoseconds" << endl;
    file << "Sredni czas dla operacji dodawania w asm: " << total_floatAdd_asm_duration / 10 << " nanoseconds" << endl;
    file << "Sredni czas dla operacji odejmowania w asm: " << total_floatSub_asm_duration / 10 << " nanoseconds" << endl;
    file << "Sredni czas dla operacji mnożenia w asm: " << total_floatMul_asm_duration / 10 << " nanoseconds" << endl;
    file << "Sredni czas dla operacji dzielenia w asm: " << total_floatDiv_asm_duration / 10 << " nanoseconds" << endl;
    file<<endl<<endl;
    file.close();

}



pair<float, float> addInt(){
    auto start_time_intAdd = std::chrono::high_resolution_clock::now();
    int_result = int_val1 + int_val2;
    auto end_time_intAdd = std::chrono::high_resolution_clock::now();
    auto duration_intAdd = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_intAdd - start_time_intAdd).count();

    auto start_time_intAdd_asm = std::chrono::high_resolution_clock::now();

    asm volatile (
            "movl %1, %%eax;"
            "movl %2, %%edx;"
            "addl %%edx, %%eax;"
            "movl %%eax, %0;"
            : "=m" (int_result)       // Output: m - memory
            : "m" (int_val1), "m" (int_val2)  // Input: m - memory
            : "eax"                    // Zmienne rejestry
            );

    auto end_time_intAdd_asm = std::chrono::high_resolution_clock::now();
    auto duration_intAdd_asm = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_intAdd_asm - start_time_intAdd_asm).count();
    return make_pair(duration_intAdd, duration_intAdd_asm);
}

pair<float, float> subInt(){
    auto start_time_intSub = std::chrono::high_resolution_clock::now();
    int_result = int_val1 - int_val2;
    auto end_time_intSub = std::chrono::high_resolution_clock::now();
    auto duration_intSub = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_intSub - start_time_intSub).count();

    auto start_time_intSub_asm = std::chrono::high_resolution_clock::now();

    asm volatile (
            "movl %1, %%eax;"
            "movl %2, %%edx;"
            "subl %%edx, %%eax;"
            "movl %%eax, %0;"
            : "=m" (int_result)       // Output: m - memory
            : "m" (int_val1), "m" (int_val2)  // Input: m - memory
            : "eax"                    // Zmienne rejestry
            );

    auto end_time_intSub_asm = std::chrono::high_resolution_clock::now();
    auto duration_intSub_asm = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_intSub_asm - start_time_intSub_asm).count();
    return make_pair(duration_intSub, duration_intSub_asm);
}

pair<float, float> mulInt() {
    auto start_time_intMul = std::chrono::high_resolution_clock::now();
    int_result = int_val1 * int_val2;
    auto end_time_intMul = std::chrono::high_resolution_clock::now();
    auto duration_intMul = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_intMul - start_time_intMul).count();

    auto start_time_intMul_asm = std::chrono::high_resolution_clock::now();

    asm volatile (
            "movl %1, %%eax;"
            "movl %2, %%edx;"
            "imull %%edx, %%eax;"
            "movl %%eax, %0;"
            : "=m" (int_result) // Output: m - memory, r - register
            : "m" (int_val1), "m" (int_val2) // Input:
            : "eax", "edx" // Effected registers
            );

    auto end_time_intMul_asm = std::chrono::high_resolution_clock::now();
    auto duration_intMul_asm = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_intMul_asm - start_time_intMul_asm).count();
    return make_pair(duration_intMul, duration_intMul_asm);
}

pair<float, float> divInt() {
    auto start_time_intDiv = std::chrono::high_resolution_clock::now();
    int_result = int_val1 / int_val2;
    auto end_time_intDiv = std::chrono::high_resolution_clock::now();
    auto duration_intDiv = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_intDiv - start_time_intDiv).count();

    auto start_time_intDiv_asm = std::chrono::high_resolution_clock::now();

    asm volatile (
            "movl %1, %%eax;"
            "movl %2, %%ecx;"      // Przeładuj dzielnik do rejestru ecx
            "xorl %%edx, %%edx;"   // Wyczyść edx, który jest używany do przechowywania reszty
            "idivl %%ecx;"         // Dzielenie eax przez ecx, wynik w eax, reszta w edx
            "movl %%eax, %0;"
            : "=m" (int_result) // Output: m - memory, r - register
            : "m" (int_val1), "m" (int_val2) // Input:
            : "eax", "ecx", "edx" // Effected registers
            );

    auto end_time_intDiv_asm = std::chrono::high_resolution_clock::now();
    auto duration_intDiv_asm = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time_intDiv_asm - start_time_intDiv_asm).count();
    return make_pair(duration_intDiv, duration_intDiv_asm);
}

pair<float, float> addFloat() {
    auto start_time_floatAdd = chrono::high_resolution_clock::now();
    float_result = float_val1 + float_val2;
    auto end_time_floatAdd = chrono::high_resolution_clock::now();
    auto duration_floatAdd = chrono::duration_cast<chrono::nanoseconds>(end_time_floatAdd - start_time_floatAdd).count();

    auto start_time_floatAdd_asm = chrono::high_resolution_clock::now();

    asm volatile (
            "flds %1;"       // Wczytaj a na stos zmiennoprzecinkowy
            "flds %2;"       // Wczytaj b na stos zmiennoprzecinkowy
            "faddp;"         // Dodaj a do b
            "fstps %0; "      // Wynik zapisz do zmiennej result
            : "=m" (float_result)   // Wyjście - zmienna result
            : "m" (float_val1), "m" (float_val2) // Wejście - zmienne a i b
            );

    auto end_time_floatAdd_asm = chrono::high_resolution_clock::now();
    auto duration_floatAdd_asm = chrono::duration_cast<chrono::nanoseconds>(end_time_floatAdd_asm - start_time_floatAdd_asm).count();
    return make_pair(duration_floatAdd, duration_floatAdd_asm);
}

pair<float, float> subFloat() {
    auto start_time_floatSub = chrono::high_resolution_clock::now();
    float_result = float_val1 - float_val2;
    auto end_time_floatSub = chrono::high_resolution_clock::now();
    auto duration_floatSub = chrono::duration_cast<chrono::nanoseconds>(end_time_floatSub - start_time_floatSub).count();

    auto start_time_floatSub_asm = chrono::high_resolution_clock::now();

    asm volatile (
            "flds %1;"
            "flds %2;"
            "fsubp;"
            "fstps %0;"
            : "=m" (float_result)
            : "m" (float_val1), "m" (float_val2)
            : // no clobbered registers
            );

    auto end_time_floatSub_asm = chrono::high_resolution_clock::now();
    auto duration_floatSub_asm = chrono::duration_cast<chrono::nanoseconds>(end_time_floatSub_asm - start_time_floatSub_asm).count();
    return make_pair(duration_floatSub, duration_floatSub_asm);
}

pair<float, float> mulFloat() {
    auto start_time_floatMul = chrono::high_resolution_clock::now();
    float_result = float_val1 * float_val2;
    auto end_time_floatMul = chrono::high_resolution_clock::now();
    auto duration_floatMul = chrono::duration_cast<chrono::nanoseconds>(end_time_floatMul - start_time_floatMul).count();

    auto start_time_floatMul_asm = chrono::high_resolution_clock::now();

    asm volatile (
            "flds %1;"
            "flds %2;"
            "fmulp;"
            "fstps %0;"
            : "=m" (float_result)
            : "m" (float_val1), "m" (float_val2)
            : // no clobbered registers
            );

    auto end_time_floatMul_asm = chrono::high_resolution_clock::now();
    auto duration_floatMul_asm = chrono::duration_cast<chrono::nanoseconds>(end_time_floatMul_asm - start_time_floatMul_asm).count();
    return make_pair(duration_floatMul, duration_floatMul_asm);
}

pair<float, float> divFloat() {
    auto start_time_floatDiv = chrono::high_resolution_clock::now();
    float_result = float_val1 / float_val2;
    auto end_time_floatDiv = chrono::high_resolution_clock::now();
    auto duration_floatDiv = chrono::duration_cast<chrono::nanoseconds>(end_time_floatDiv - start_time_floatDiv).count();

    auto start_time_floatDiv_asm = chrono::high_resolution_clock::now();

    asm volatile (
            "flds %1;"
            "flds %2;"
            "fdivp;"
            "fstps %0;"
            : "=m" (float_result)
            : "m" (float_val1), "m" (float_val2)
            : // no clobbered registers
            );

    auto end_time_floatDiv_asm = chrono::high_resolution_clock::now();
    auto duration_floatDiv_asm = chrono::duration_cast<chrono::nanoseconds>(end_time_floatDiv_asm - start_time_floatDiv_asm).count();
    return make_pair(duration_floatDiv, duration_floatDiv_asm);
}
