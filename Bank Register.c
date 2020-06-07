    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define WORDLENGTH 100
    #define MAX 10000
    #define LENGTH 30

    struct accounts
    {
        char owner[LENGTH];
        int accountnr;
        int balance;
    };
    typedef struct accounts Accounts;

    Accounts createAccount(int accountnr, char name[], int balance){
    Accounts a;
    a.accountnr = accountnr;
    a.balance = 0;
    strcpy(a.owner, name);
    return a;
    }

    void ignoref(FILE* f, size_t n, char c) //hämtat från www.cplusplus.com/forum/beginner/107761, används för att undvika blanksteg i scanf-funktioner
    {
        while(n-- && (fgetc( f ) != c)){
        ;}
    }

    void regAccounts(Accounts reg[], int *pNrOfAccounts){
        char again[WORDLENGTH] = "yes", name[WORDLENGTH], accountsRegister[LENGTH];
        int accountnr, i, balance, nrOfAccounts;
        int nrExists = 0;

        while(strcmp(again,"yes")==0){
            printf("Account number: ");
            scanf("%d", &accountnr);
            ignoref(stdin, (-1), '\n');
            if(accountnr == 0)
                printf("The entered account number is invalid. Try again.\n");
            else{
                for(i = 0; i < *pNrOfAccounts; i++){
                    if(accountnr == reg[i].accountnr)
                    nrExists = 1;
                }
            if (nrExists == 0){
                printf("Owner's full name: ");
                fgets(name, sizeof(name), stdin);
                name[strlen(name)-1]='\0';
                reg[*pNrOfAccounts] = createAccount(accountnr, name, balance);
                (*pNrOfAccounts)++;
            }
                else {
                    printf("That account number already exists. Try again. \n");
                    nrExists = 0;
                }
            }
                printf("Do you wish to continue registering accounts? (yes/no): ");
                gets(again);
        }
    }


    void printRegister(Accounts reg[], int nrOfAccounts)
    {
        int i;
        for(i=0;i<nrOfAccounts;i++){
        printf("%d. Account number: %.6d, Owner: %s, Balance: %dkr\n",i+1, reg[i].accountnr, reg[i].owner, reg[i].balance);
        }
        printf("\n");
    }

    void readFromFile(Accounts reg[], int *pNrOfAccounts, char file[])
    {
        FILE* fp;
        fp=fopen(file, "r");
        if(fp!=NULL)
        {
            printf("File was found.\n\n");
            int accountnr, i;
            char name[LENGTH];
            int balance;
            char lastName[WORDLENGTH];
            fscanf(fp, "%d", pNrOfAccounts);
                for (i = 0; i < *pNrOfAccounts; i++){
                    fscanf(fp, "%d %s %s %d", &reg[i].accountnr, reg[i].owner, lastName, &reg[i].balance);
                    strcat(reg[i].owner, " ");
                    strcat(reg[i].owner, lastName);
                }
        }
        if(fp==NULL)
            {
            printf("File was created.\n\n");
            fp=fopen(file,"w");
            }
        fclose(fp);
    }

    void getInput(Accounts reg[], char file[])
    {
        printf("Enter a filename to search for: ");
        scanf("%s", file);
        strcat(file,".txt");
    }

    void writeToFile(Accounts reg[], int nrOfAccounts, char file[])
    {
        FILE *fp;
        fp = fopen(file, "w");
        if(fp!=NULL)
        {
            fprintf(fp, "%d\n", nrOfAccounts);
            int i;
            for(i = 0 ; i < nrOfAccounts; i++){
                fprintf(fp, "%.6d %s %d\n", reg[i].accountnr, reg[i].owner, reg[i].balance);
            }
        }
        fclose(fp);
    }

    void sortByNr(Accounts reg[], int *pNrOfAccounts)
    {
        int i, j;
        Accounts tmp;

        for(i=0;i<*pNrOfAccounts-1;i++)
        {
            for(j=0;j<*pNrOfAccounts-1-i;j++)
            {
                if(reg[j].accountnr>reg[j+1].accountnr)
                {
                    tmp=reg[j];
                    reg[j]=reg[j+1];
                    reg[j+1]=tmp;
                }
            }
        }
        system("clear");
        printf("Accounts have been sorted by account numbers.\n");
    }

    void sortByName(Accounts reg[], int nrOfAccounts)
    {
        int i, j, k;
        Accounts tmp;
        char name[WORDLENGTH];
        for(i=0;i<nrOfAccounts-1;i++)
        {
            for(j=0;j<nrOfAccounts-1-i;j++)
            {
                if(strcmp(reg[j].owner,reg[j+1].owner)>0)
                {
                    tmp=reg[j];
                    reg[j]=reg[j+1];
                    reg[j+1]=tmp;
                }
            }
        }
        system("clear");
        printf("Accounts have been sorted by the first names.\n");
    }

    void sortByBalance(Accounts reg[], int *pNrOfAccounts)
    {
        int i, j;
        Accounts tmp;

        for(i=0;i<*pNrOfAccounts-1;i++)
        {
            for(j=0;j<*pNrOfAccounts-1-i;j++)
            {
                if(reg[j].balance>reg[j+1].balance)
                {
                    tmp=reg[j];
                    reg[j]=reg[j+1];
                    reg[j+1]=tmp;
                }
            }
        }
        system("clear");
        printf("Accounts have been sorted by balance.\n");
    }

    void sortAccounts(Accounts reg[], int *pNrOfAccounts)
    {
        system("clear");
        int n;

        do
        {
            printf("1. Sort by account number.\n");
            printf("2. Sort by name.\n");
            printf("3. Sort by balance.\n");
            printf("4. Exit and return to main menu.\n");
            printf("Option: ");

            scanf("%d", &n);

            switch(n)
            {
            case 1:
                sortByNr(reg, &*pNrOfAccounts);
                ignoref(stdin, (-1), '\n');
                break;
            case 2:
                sortByName(reg, *pNrOfAccounts);
                ignoref(stdin, (-1), '\n');
                break;
            case 3:
                sortByBalance(reg, &*pNrOfAccounts);
                ignoref(stdin, (-1), '\n');
                break;
            case 4:
                return;
                break;
            default:
                printf("ERROR! Try again\n");
            }
        }
        while(n);
    }

     void searchByName(Accounts reg[], int nrOfAccounts)
    {
        int i;
        int nameFound = 0;
        char searchName[WORDLENGTH];
        system("clear");
        printf("Enter a part of a name: ");
        ignoref(stdin, (-1), '\n');
        fgets(searchName, sizeof(searchName), stdin);
        searchName[strlen(searchName)-1]='\0';

        for(i=0;i < nrOfAccounts;i++)
        {
            if(0!=strstr(reg[i].owner,searchName))
            {
                printf("%d. Account number: %.6d, Owner: %s, Balance: %dkr\n",i+1, reg[i].accountnr, reg[i].owner, reg[i].balance);
                nameFound = 1;
            }
            else if(strcmp(reg[i].owner,searchName)!=0)
                continue;
        }
        if(nameFound == 1)
            printf("Accounts found listed above. Press enter to continue or choose from following options: \n");

        else
            printf("No names found. Press enter to continue or choose from following options: \n");
    }

    void searchByNr(Accounts reg[], int nrOfAccounts)
    {
        char enteredNr[LENGTH];
        int nrExists = 0, accountnr, i;
        system("clear");
        printf("Enter account number to search for: ");
        ignoref(stdin, (-1), '\n');
        fgets(enteredNr, sizeof(enteredNr), stdin);
        accountnr = atoi(enteredNr);

        for (i = 0; i < nrOfAccounts; i++){
            if(accountnr == reg[i].accountnr){
                printf("%d. Account number: %.6d, Owner: %s, Balance: %dkr\n",i+1, reg[i].accountnr, reg[i].owner, reg[i].balance);
                nrExists = 1;
            }
        }
        if(nrExists == 1)
            printf("Accounts found listed above. Press enter to continue.\n");

        else if(nrExists == 0)
            printf("That account number doesn't exist. Press enter to try again.\n", accountnr);
    }

    void searchByBalance(Accounts reg[], int nrOfAccounts)
    {
        char minMax[WORDLENGTH];
        int min, max, found = 0, i, j;
        Accounts balance[MAX];
        system("clear");

        printf("Enter desired minimum: ");
        ignoref(stdin, (-1), '\n');
        fgets(minMax, sizeof(minMax), stdin);
        min = atoi(minMax);

        printf("Enter desired maximum: ");
        fgets(minMax, sizeof(minMax), stdin);
        max = atoi(minMax);

        for (i = 0; i < nrOfAccounts; i++){
            if (reg[i].balance >= min && reg[i].balance <= max)
            {
                balance[found] = reg[i];
                printf("%d. Account number: %.6d, Owner: %s, Balance: %dkr\n",i+1, reg[i].accountnr, reg[i].owner, reg[i].balance);
                found++;
            }
        }
        if(found > 0)
            printf("Accounts found listed above. Press enter to continue.\n");
        else
            printf("No accounts were found. Press enter to try again.\n");
    }

    int deposit()
    {
        int amount;
        printf("Enter desired amount to deposit: ");
        scanf("%d", &amount);
        printf("You successfully deposited %dkr to the selected account!\n\n", amount);
        return amount;
    }

    int withdraw(Accounts reg)
    {
        int amount, balance = reg.balance;
        printf("Enter desired amount to withdraw: ");
        scanf("%d", &amount);
        printf("You succesfully withdrew %dkr from the selected account!\n\n", amount);
        balance -= amount;
        if(balance < 0)
        {
            printf("You attempted to withdraw more than available. Try again.\n");
            return 0;
        }
        else return amount;
    }

    void depositWithdrawByNr(Accounts reg[], int nrOfAccounts)
    {
        int i, found = 0, n, accountnr;
        printf("Entered desired account number for withdrawal/deposit: ");
        scanf("%d", &accountnr);
        for(i = 0; i < nrOfAccounts; i++)
        {
            if(accountnr == reg[i].accountnr){
                do
                {
                    printf("1. Deposit\n");
                    printf("2. Withdraw\n");
                    printf("3. Exit and return to previous menu.\n");
                    printf("Option: ");
                    scanf("%d", &n);
                    switch (n) {
                        case 1:
                            reg[i].balance += deposit();
                            break;
                        case 2:
                            reg[i].balance -= withdraw(reg[i]);
                            break;
                        case 3:
                            return;
                            break;
                        default:  printf("That choice is unavailable. Try again.\n");
                    }
                found = 1;
                } while(n);
            }
        }
        if(found == 0)
            printf("The account number wasn't found. Try again.\n");
    }

    void depositWithdrawByName(Accounts reg[], int nrOfAccounts)
    {
        searchByName(reg, nrOfAccounts);
        depositWithdrawByNr(reg, nrOfAccounts);
    }

    void depositWithdraw(Accounts reg[], int *pNrOfAccounts)
    {
        int n;

        do
        {
            printf("1. Search account for withdrawal/deposit with account number.\n");
            printf("2. Search account for withdrawal/deposit with name.\n");
            printf("3. Exit and return to main menu.\n");
            printf("Option: ");

            scanf("%d", &n);

            switch(n)
            {
            case 1:
                depositWithdrawByNr(reg, *pNrOfAccounts);
                ignoref(stdin, (-1), '\n');
                break;
            case 2:
                depositWithdrawByName(reg, *pNrOfAccounts);
                ignoref(stdin, (-1), '\n');
                break;
            case 3:
                return;
                break;
            default:
                printf("ERROR! Try again");
            }
        }
        while(n);
    }


    void searchAccounts(Accounts reg[], int *pNrOfAccounts)
    {
        int n;

        do
        {
            printf("1. Search with account number.\n");
            printf("2. Search with name.\n");
            printf("3. Search with balance (max/min).\n");
            printf("4. Exit and return to main menu.\n");
            printf("Option: ");

            scanf("%d", &n);

            switch(n)
            {
            case 1:
                searchByNr(reg, *pNrOfAccounts);
                ignoref(stdin, (-1), '\n');
                break;
            case 2:
                searchByName(reg, *pNrOfAccounts);
                ignoref(stdin, (-1), '\n');
                break;
            case 3:
                searchByBalance(reg, *pNrOfAccounts);
                ignoref(stdin, (-1), '\n');
                break;
            case 4:
                return;
                break;
            default:
                printf("ERROR! Try again");
            }
        }
        while(n);
    }

    void cancelByAccountNr(Accounts reg[], int *pNrOfAccounts)
    {
        int found = 0, i, j, accountnr;
        printf("Enter account number for the account you wish to cancel: ");
        scanf("%d", &accountnr);
        ignoref(stdin, (-1), '\n');
        for(i = 0; i < *pNrOfAccounts; i++)
        {
            if(accountnr == reg[i].accountnr)
            {
                found = 1;
                if(reg[i].balance == 0)
                {
                    printf("The account was cancelled successfully.\n");
                    for(j = 0; j < (*pNrOfAccounts); j++)
                    {
                            reg[j] = reg[j+1];
                            (*pNrOfAccounts)--;
                    }
                }
                else printf("The balance needs to be 0 before you can cancel the account.\n");
            }
        }
        if(found == 0)
            printf("That account doesn't exist. Try again.\n");
    }

    void cancelByAccountName(Accounts reg[], int *pNrOfAccounts)
    {
        searchByName(reg, *pNrOfAccounts);
        cancelByAccountNr(reg, *&pNrOfAccounts);
    }

    void cancelAccount(Accounts accountsRegister[], int *pNrOfAccounts)
    {
        int n;
        system("clear");
        do
        {
            printf("1. Cancel account using account number.\n");
            printf("2. Cancel account using name\n");
            printf("3. Exit and return to previous menu.\n");
            printf("Option: ");
            scanf("%d", &n);

            switch(n)
            {
            case 1:
                cancelByAccountNr(accountsRegister, &*pNrOfAccounts);
                break;
            case 2:
                cancelByAccountName(accountsRegister, &*pNrOfAccounts);
                break;
            case 3:
                return;
                break;
            default:
                printf("ERROR! Try again");
            }
        }
        while(n);
    }

    float avg(Accounts reg[], int *pNrOfAccounts)
    {
        int i;
        double avg = 0;
        for(i = 0; i < *pNrOfAccounts; i++)
        {
            avg += reg[i].balance;
        }
        return (avg / *pNrOfAccounts);
    }

    void findMedian(Accounts reg[], int *pNrOfAccounts, int *pMedian)
    {
        if (*pNrOfAccounts % 2 == 0)
            *pMedian = (reg[(*pNrOfAccounts/2)-1].balance + reg[*pNrOfAccounts/2].balance)/2;
        else
            *pMedian = (reg[(*pNrOfAccounts/2)].balance);
    }

    void findMode(Accounts reg[], int *pNrOfAccounts, int *pMode)
    {
        int found[MAX], i, j, totalFound = 0;
        *pMode = 0;
        for(i = 0; i < *pNrOfAccounts; i++)
        {
            for(j = i +1; j < *pNrOfAccounts; j++)
            {
                if(reg[i].balance == reg[i].balance)
                    found[i]++;
            }
        }
        for(i = 0; i < *pNrOfAccounts; i++)
        {
            if(found[i] > totalFound)
            {
                totalFound = found[i];
                *pMode = reg[i].balance;
            }
        }
    }

    void statistics(Accounts reg[], int *pNrOfAccounts)
    {
        double average;
        int median, mode;
        average = avg(reg, &*pNrOfAccounts);
        findMedian(reg, &*pNrOfAccounts, &median);
        findMode(reg, &*pNrOfAccounts, &mode);

        printf("Average: %.2f\n", average);
        printf("Median: %d\n", median);
        printf("Mode: %d\n", mode);
    }

    void transfer(Accounts reg[], int nrOfAccounts)
    {
        int from, to, amount, i;
        printRegister(reg, nrOfAccounts);
        printf("\nEnter the number of the account to transfer money from: ");
        scanf("%d", &from);
        ignoref(stdin, (-1), '\n');
        printf("\nEnter the number of the account to transfer money to: ");
        scanf("%d", &to);
        ignoref(stdin, (-1), '\n');
        printf("\nEnter amount of money you wish to transfer: ");
        scanf("%d", &amount);
        ignoref(stdin, (-1), '\n');
            if(amount > reg[from - 1].balance)
                printf("You have attempted to transfer more money than available. Try again.\n\n");
            else
            {
                reg[from - 1].balance -= amount;
                reg[to - 1].balance += amount;
                printf("The transfer was successful.\n\n");
            }
    }

    void menu(Accounts accountsRegister[], int *pNrOfAccounts, char file[])
    {
        int exit = 0;
        int nrOfAccounts = *pNrOfAccounts;
        int n;
        do
        {
            printf("1. Register accounts\n");
            printf("2. Print accounts\n");
            printf("3. Sort accounts by account number, name or balance\n");
            printf("4. Search for accounts\n");
            printf("5. Withdraw or deposit on an account\n");
            printf("6. Cancel an account\n");
            printf("7. Show statistics\n");
            printf("8. Transfer money from one account to another\n");
            printf("9. Exit and save into file\n");
            printf("Option: ");

            scanf("%d", &n);

            switch(n)
            {
            case 1:
                system("clear");
                regAccounts(accountsRegister, &*pNrOfAccounts);
                break;
            case 2:
                system("clear");
                printRegister(accountsRegister, *pNrOfAccounts);
                break;
            case 3:
                system("clear");
                sortAccounts(accountsRegister, &*pNrOfAccounts);
                break;
            case 4:
                system("clear");
                searchAccounts(accountsRegister, &*pNrOfAccounts);
                break;
            case 5:
                system("clear");
                depositWithdraw(accountsRegister, &*pNrOfAccounts);
                break;
            case 6:
                system("clear");
                cancelAccount(accountsRegister, &*pNrOfAccounts);
                break;
            case 7:
                system("clear");
                statistics(accountsRegister, &*pNrOfAccounts);
                break;
            case 8:
                system("clear");
                transfer(accountsRegister, *pNrOfAccounts);
                break;
            case 9:
                exit = 1;
                writeToFile(accountsRegister, *pNrOfAccounts, file);
                return;
                break;
            default:
                printf("ERROR! Try again");
            }
        }
        while(!exit);
    }

    int main(void)
    {
        char file[WORDLENGTH];
        Accounts accountsRegister[LENGTH];
        int nrOfAccounts = 0;
        getInput(accountsRegister, file);
        readFromFile(accountsRegister, &nrOfAccounts, file);
        menu(accountsRegister, &nrOfAccounts, file);
        return 0;
    }
