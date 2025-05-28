#include <cstring>
#include <iostream>
#include <stdexcept>

class Deposit {
   protected:
    char* accountNumber;
    char* creationDate;
    double annualRate;
    double currentAmount;
    char* lastInterestDate;

    void copyString(char*& dest, const char* source) {
        if (source) {
            dest = new char[strlen(source) + 1];
            strcpy(dest, source);
        } else {
            dest = nullptr;
        }
    }

   public:
    Deposit(const char* accNum = "", const char* crDate = "", double rate = 0.0,
            double amount = 0.0, const char* lastDate = "")
        : annualRate(rate), currentAmount(amount) {
        copyString(accountNumber, accNum);
        copyString(creationDate, crDate);
        copyString(lastInterestDate, lastDate);

        if (annualRate < 0) throw std::invalid_argument("Rate cannot be negative");
        if (currentAmount < 0) throw std::invalid_argument("Amount cannot be negative");
    }

    virtual ~Deposit() {
        delete[] accountNumber;
        delete[] creationDate;
        delete[] lastInterestDate;
    }

    Deposit(const Deposit& other)
        : annualRate(other.annualRate), currentAmount(other.currentAmount) {
        copyString(accountNumber, other.accountNumber);
        copyString(creationDate, other.creationDate);
        copyString(lastInterestDate, other.lastInterestDate);
    }

    Deposit& operator=(const Deposit& other) {
        if (this != &other) {
            delete[] accountNumber;
            delete[] creationDate;
            delete[] lastInterestDate;
            copyString(accountNumber, other.accountNumber);
            copyString(creationDate, other.creationDate);
            copyString(lastInterestDate, other.lastInterestDate);
            annualRate = other.annualRate;
            currentAmount = other.currentAmount;
        }
        return *this;
    }

    Deposit(Deposit&& other) noexcept
        : accountNumber(other.accountNumber),
          creationDate(other.creationDate),
          annualRate(other.annualRate),
          currentAmount(other.currentAmount),
          lastInterestDate(other.lastInterestDate) {
        other.accountNumber = nullptr;
        other.creationDate = nullptr;
        other.lastInterestDate = nullptr;
    }

    Deposit& operator=(Deposit&& other) noexcept {
        if (this != &other) {
            delete[] accountNumber;
            delete[] creationDate;
            delete[] lastInterestDate;
            accountNumber = other.accountNumber;
            creationDate = other.creationDate;
            lastInterestDate = other.lastInterestDate;
            annualRate = other.annualRate;
            currentAmount = other.currentAmount;
            other.accountNumber = nullptr;
            other.creationDate = nullptr;
            other.lastInterestDate = nullptr;
        }
        return *this;
    }

    virtual void Print(std::ostream& os) const = 0;
    virtual Deposit* Clone() const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Deposit& deposit) {
        deposit.Print(os);
        return os;
    }
};

class DemandDeposit : public Deposit {
   public:
    DemandDeposit(const char* accNum, const char* crDate, double rate, double amount,
                  const char* lastDate)
        : Deposit(accNum, crDate, rate, amount, lastDate) {}

    DemandDeposit* Clone() const override { return new DemandDeposit(*this); }

    void Print(std::ostream& os) const override {
        os << "Type: Demand Deposit\n"
           << "Account: " << accountNumber << "\nCreated: " << creationDate
           << "\nRate: " << annualRate << "%\nAmount: $" << currentAmount
           << "\nLast interest: " << lastInterestDate << "\n";
    }
};

class ConditionalDeposit : public Deposit {
    char* closingCondition;

   public:
    ConditionalDeposit(const char* accNum, const char* crDate, double rate, double amount,
                       const char* lastDate, const char* condition)
        : Deposit(accNum, crDate, rate, amount, lastDate) {
        copyString(closingCondition, condition);
    }

    ~ConditionalDeposit() override { delete[] closingCondition; }

    ConditionalDeposit(const ConditionalDeposit& other) : Deposit(other) {
        copyString(closingCondition, other.closingCondition);
    }

    ConditionalDeposit& operator=(const ConditionalDeposit& other) {
        if (this != &other) {
            Deposit::operator=(other);
            delete[] closingCondition;
            copyString(closingCondition, other.closingCondition);
        }
        return *this;
    }

    ConditionalDeposit(ConditionalDeposit&& other) noexcept
        : Deposit(std::move(other)), closingCondition(other.closingCondition) {
        other.closingCondition = nullptr;
    }

    ConditionalDeposit& operator=(ConditionalDeposit&& other) noexcept {
        if (this != &other) {
            Deposit::operator=(std::move(other));
            delete[] closingCondition;
            closingCondition = other.closingCondition;
            other.closingCondition = nullptr;
        }
        return *this;
    }

    ConditionalDeposit* Clone() const override { return new ConditionalDeposit(*this); }

    void Print(std::ostream& os) const override {
        os << "Type: Conditional Deposit\n"
           << "Account: " << accountNumber << "\nCreated: " << creationDate
           << "\nRate: " << annualRate << "%\nAmount: $" << currentAmount
           << "\nLast interest: " << lastInterestDate << "\nCondition: " << closingCondition
           << "\n";
    }
};

class TermDeposit : public Deposit {
   protected:
    int depositTerm;

   public:
    TermDeposit(const char* accNum, const char* crDate, double rate, double amount,
                const char* lastDate, int term)
        : Deposit(accNum, crDate, rate, amount, lastDate), depositTerm(term) {
        if (term <= 0) throw std::invalid_argument("Term must be positive");
    }

    TermDeposit* Clone() const override { return new TermDeposit(*this); }

    void Print(std::ostream& os) const override {
        os << "Type: Term Deposit\n"
           << "Account: " << accountNumber << "\nCreated: " << creationDate
           << "\nRate: " << annualRate << "%\nAmount: $" << currentAmount
           << "\nLast interest: " << lastInterestDate << "\nTerm: " << depositTerm << " months\n";
    }
};

class NonWithdrawableTermDeposit : public TermDeposit {
    int depositPeriod;

   public:
    NonWithdrawableTermDeposit(const char* accNum, const char* crDate, double rate, double amount,
                               const char* lastDate, int term, int period)
        : TermDeposit(accNum, crDate, rate, amount, lastDate, term), depositPeriod(period) {
        if (period <= 0) throw std::invalid_argument("Period must be positive");
    }

    NonWithdrawableTermDeposit* Clone() const override {
        return new NonWithdrawableTermDeposit(*this);
    }

    void Print(std::ostream& os) const override {
        os << "Type: Non-Withdrawable Term Deposit\n"
           << "Account: " << accountNumber << "\nCreated: " << creationDate
           << "\nRate: " << annualRate << "%\nAmount: $" << currentAmount
           << "\nLast interest: " << lastInterestDate << "\nTerm: " << depositTerm << " months"
           << "\nPeriod: " << depositPeriod << " months\n";
    }
};

class WithdrawableTermDeposit : public TermDeposit {
    double reducedRate;
    double initialAmount;

   public:
    WithdrawableTermDeposit(const char* accNum, const char* crDate, double rate, double amount,
                            const char* lastDate, int term, double rRate, double iAmount)
        : TermDeposit(accNum, crDate, rate, amount, lastDate, term),
          reducedRate(rRate),
          initialAmount(iAmount) {
        if (rRate < 0) throw std::invalid_argument("Reduced rate cannot be negative");
        if (iAmount < 0) throw std::invalid_argument("Initial amount cannot be negative");
    }

    WithdrawableTermDeposit* Clone() const override { return new WithdrawableTermDeposit(*this); }

    void Print(std::ostream& os) const override {
        os << "Type: Withdrawable Term Deposit\n"
           << "Account: " << accountNumber << "\nCreated: " << creationDate
           << "\nRate: " << annualRate << "%\nAmount: $" << currentAmount
           << "\nLast interest: " << lastInterestDate << "\nTerm: " << depositTerm << " months"
           << "\nReduced rate: " << reducedRate << "%"
           << "\nInitial amount: $" << initialAmount << "\n";
    }
};

class DepositArray {
    Deposit** data;
    size_t size;
    size_t capacity;

    void resize(size_t newCapacity) {
        Deposit** newData = new Deposit*[newCapacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i]->Clone();
            delete data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

   public:
    DepositArray() : data(nullptr), size(0), capacity(0) {}

    DepositArray(const DepositArray& other) : size(other.size), capacity(other.capacity) {
        data = new Deposit*[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i]->Clone();
        }
    }

    DepositArray& operator=(const DepositArray& other) {
        if (this != &other) {
            for (size_t i = 0; i < size; ++i) delete data[i];
            delete[] data;

            size = other.size;
            capacity = other.capacity;
            data = new Deposit*[capacity];
            for (size_t i = 0; i < size; ++i) data[i] = other.data[i]->Clone();
        }
        return *this;
    }

    DepositArray(DepositArray&& other) noexcept
        : data(other.data), size(other.size), capacity(other.capacity) {
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    DepositArray& operator=(DepositArray&& other) noexcept {
        if (this != &other) {
            for (size_t i = 0; i < size; ++i) delete data[i];
            delete[] data;
            data = other.data;
            size = other.size;
            capacity = other.capacity;
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    ~DepositArray() {
        for (size_t i = 0; i < size; ++i) delete data[i];
        delete[] data;
    }

    void add(const Deposit& deposit) {
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = deposit.Clone();
    }

    void remove(size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        delete data[index];
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
    }

    void printAll(std::ostream& os) const {
        for (size_t i = 0; i < size; ++i) {
            os << *data[i] << "------------------------\n";
        }
    }

    size_t getSize() const { return size; }
};

// Тестирование
int main() {
    DepositArray arr;
    arr.add(DemandDeposit("ACC001", "2025-01-01", 5.0, 10000, "2025-12-31"));
    arr.add(ConditionalDeposit("ACC002", "2025-02-15", 4.5, 50000, "2025-12-31", "Until marriage"));
    arr.add(NonWithdrawableTermDeposit("ACC003", "2019-03-10", 7.0, 100000, "2025-12-31", 24, 6));
    arr.add(WithdrawableTermDeposit("ACC004", "2020-04-20", 6.5, 200000, "2025-12-31", 12, 3.0,
                                    200000));

    std::cout << "All deposits:\n";
    arr.printAll(std::cout);

    std::cout << "Removing second element...\n";
    arr.remove(1);
    std::cout << "After removal:\n";
    arr.printAll(std::cout);

    std::cout << "Copy and print copied array:\n";
    DepositArray copy = arr;
    copy.printAll(std::cout);

    std::cout << "Move array into new one and print:\n";
    DepositArray moved = std::move(arr);
    moved.printAll(std::cout);

    std::cin.ignore();
    std::cin.get();
    return 0;
}
