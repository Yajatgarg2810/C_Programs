#include <stdio.h>
#include <string.h>

#define N strlen(gen_poly)

char data[28];
char check_value[28];
char gen_poly[10];

int data_length, i, j;

void XOR() {
    for (j = 1; j < N; j++) {
        check_value[j] = (check_value[j] == gen_poly[j] ? '0' : '1');
    }
}

void CRC() {
    // Copy initial data to check_value
    for (i = 0; i < N; i++) {
        check_value[i] = data[i];
    }

    do {
        if (check_value[0] == '1') {
            XOR();
        }

        // Shift left by 1 position
        for (j = 0; j < N - 1; j++) {
            check_value[j] = check_value[j + 1];
        }
        check_value[j] = data[i++];
    } while (i <= data_length + N - 1);
}

void receiver() {
    printf("Enter the received data: ");
    scanf("%s", data);
    printf("Data Received: %s\n", data);

    CRC();

    for (i = 0; (i < N - 1) && (check_value[i] != '1'); i++);

    if (i < N - 1) {
        printf("\nError detected\n\n");
    } else {
        printf("\nNo error detected\n");
    }
}

int main() {
    printf("\nEnter data to be transmitted: ");
    scanf("%s", data);

    printf("\nEnter the generating polynomial: ");
    scanf("%s", gen_poly);

    data_length = strlen(data);

    for (i = data_length; i < data_length + N - 1; i++) {
        data[i] = '0';
    }
    data[i] = '\0'; // Null-terminate the string

    printf("\n________________");
    printf("\nData padded with n-1 zeroes: %s", data);
    printf("\n__________________\n");

    CRC();

    printf("\n CRC check value is: %s\n", check_value);

    for (i = data_length; i < data_length + N - 1; i++) {
        data[i] = check_value[i - data_length];
    }
    data[i] = '\0'; // Null-terminate the string

    printf("\n____________________");
    printf("\nFinal data to be sent: %s", data);
    printf("\n_________________\n");

    receiver();

    return 0;
}
