#include <stdio.h>
#include <stdint.h>


// nbo->hbo 바이트 순서 변경
uint32_t swap_bytes(uint32_t num) {
    return ((num >> 24) & 0xFF) |
           ((num >> 8) & 0xFF00) |
           ((num << 8) & 0xFF0000) |
           ((num << 24) & 0xFF000000);
}
   // main 함수, 프로그램 실행될 때 가장 먼저 호출되는 함수.
   // 만약 커맨드 라인 인수가 add-nbo th.bin fi.bin 즉 3개가 아니라면 
   // prinft문을 출력하게 한다. 
int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("syntax : add-nbo <file1> <file2>\n");
        printf("sample : add-nbo a.bin b.bin\n");
        return 1;
    }
    // thousand.bin과 five-hundred.bin을 불러온다.
    FILE* file1 = fopen(argv[1], "rb");
    FILE* file2 = fopen(argv[2], "rb");

    // 개발자의 바른자세
    if (file1 == NULL || file2 == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }

    // 32bit 숫자가 저장된 파일들을 읽어온다 thousand.bin과 five-hundred.bin
    // 을 차례로 읽어들인다.
    uint32_t num1, num2;
    fread(&num1, sizeof(uint32_t), 1, file1);
    fread(&num2, sizeof(uint32_t), 1, file2);
    //파일을 읽어오면 꼭 fclose로 닫아줘야 한다.
    fclose(file1);
    fclose(file2);
    // 읽어들여온 파일을 바이트 순서를 변경하기 위해 함수 swap_bytes 인자에
    // 넣어 변환하도록 지시한다.
    num1 = swap_bytes(num1);
    num2 = swap_bytes(num2); 

    // 1000(0x3e8) + 500(0x1f4) = 1500(0x5dc)로 계산
    uint32_t sum = num1 + num2;

    printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", num1, num1, num2, num2, sum, sum);

    return 0;
}
