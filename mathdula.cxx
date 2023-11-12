#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int playerLevel = 1;
int intelligence = 1;
int wisdom = 4;
int manaPool;
int unassignedAttributePoints = 0;
int monsterHitPoints = 10;

void levelUp();
void distributeAttributePoints();
void updateManaPool();
void handleTrap();
void handleMonster();
int calculateDamage(int numericalCharacters, int operators);
void gameover();

int main() {
    srand((unsigned)time(NULL));

    while (playerLevel <= 15) {
        printf("---------------\n");
        printf("Current Level: %d\n", playerLevel);
        printf("Intelligence: %d\n", intelligence);
        printf("Wisdom: %d\n", wisdom);
        printf("---------------\n");

        // Proceed to the next encounter
        printf("Press Enter to proceed to the next encounter...\n");
        while (getchar() != '\n');

        // Randomly simulate encounters (trap or monster)
        if (rand() % 2 == 0) {
            handleTrap();
        } else {
            handleMonster();
        }

        // Check for leveling up
        if ((playerLevel % 3 == 0) && (playerLevel <= 15)) {
            levelUp();
        }
    }

    printf("Congratulations! You've completed the game by reaching Level 15!\n");

    return 0;
}

void levelUp() {
    printf("Congratulations! You've leveled up to Level %d\n", playerLevel + 1);
    playerLevel++;

    // Adjust mana pool based on new attributes
    updateManaPool();

    // Award 2 distributable attribute points
    unassignedAttributePoints += 2;
    distributeAttributePoints();

    // Increase monster hit points exponentially for the next encounter
    monsterHitPoints *= 2;
}

void distributeAttributePoints() {
    while (unassignedAttributePoints > 0) {
        printf("Unassigned Attribute Points: %d\n", unassignedAttributePoints);
        printf("1. Intelligence\n");
        printf("2. Wisdom\n");
        printf("Select an attribute to assign points (1 or 2): ");

        int choice;
        scanf("%d", &choice);
        while (getchar() != '\n');  // Clear input buffer

        if (choice == 1) {
            printf("Assign points to Intelligence: ");
            int points;
            scanf("%d", &points);
            while (getchar() != '\n');  // Clear input buffer
            intelligence += points;
            unassignedAttributePoints -= points;
        } else if (choice == 2) {
            printf("Assign points to Wisdom: ");
            int points;
            scanf("%d", &points);
            while (getchar() != '\n');  // Clear input buffer
            wisdom += points;
            unassignedAttributePoints -= points;
        } else {
            printf("Invalid choice. Please select 1 or 2.\n");
        }
    }
}

void updateManaPool() {
    manaPool = wisdom;
    printf("Mana Pool has been updated. Current Mana Pool: %d\n", manaPool);
}

void handleTrap() {
    printf("Oh no! You've triggered a trap!\n");

    // Generate a random linear equation for the trap
    int a = rand() % 10 + 1; // Random coefficient
    int b = rand() % 10 + 1; // Random constant
    int x = rand() % 10 + 1; // Random variable

    int result = a * x + b;
    int playerAnswer;

    printf("Solve for x in the equation: %dx + %d = %d\n", a, b, result);
    printf("Your Answer: ");
    scanf("%d", &playerAnswer);
    while (getchar() != '\n');  // Clear input buffer

    if (playerAnswer == x) {
        printf("You successfully avoided damage!\n");
    } else {
        printf("Incorrect! You take damage!\n");
        gameover();
    }
}

void handleMonster() {
    int currentMonsterHitPoints = monsterHitPoints;
    printf("A wild monster appears with %d hit points!\n", currentMonsterHitPoints);

    // Player attacks the monster
    int numericalCharacters, operators;
    printf("Enter the number of numerical characters in your spell: ");
    scanf("%d", &numericalCharacters);
    while (getchar() != '\n');  // Clear input buffer
    printf("Enter the number of operators in your spell: ");
    scanf("%d", &operators);
    while (getchar() != '\n');  // Clear input buffer

    // Calculate damage using the provided formula
    int damage = calculateDamage(numericalCharacters, operators);

    // Reduce monster hit points
    currentMonsterHitPoints -= damage;

    if (currentMonsterHitPoints <= 0) {
        printf("You defeated the monster!\n");

        // Increase monster hit points exponentially for the next encounter
        monsterHitPoints *= 2;
    } else {
        printf("The monster has %d hit points remaining!\n", currentMonsterHitPoints);

        // Monster counter-attacks with a linear equation
        printf("The monster counter-attacks with a linear equation!\n");
        int a = rand() % 10 + 1; // Random coefficient
        int b = rand() % 10 + 1; // Random constant
        int x = rand() % 10 + 1; // Random variable

        int monsterEquationResult = a * x + b;
        int playerAnswer;

        printf("Solve for x in the equation: %dx + %d = %d\n", a, b, monsterEquationResult);
        printf("Your Answer: ");
        scanf("%d", &playerAnswer);
        while (getchar() != '\n');  // Clear input buffer

        if (playerAnswer == x) {
            printf("You successfully avoided the counter-attack!\n");
        } else {
            printf("Incorrect! You take damage from the counter-attack!\n");
            gameover();
        }
    }
}

int calculateDamage(int numericalCharacters, int operators) {
    if (intelligence == 0 || wisdom == 0) {
        printf("Error: Intelligence or Wisdom cannot be zero. Ending the game.\n");
        exit(1);
    }

    int y = operators % 2 == 0 ? 4 : 2; // Using × or ÷ adds 4, using + or - adds 2
    return y * (numericalCharacters + (int)(0.5 * y));
}

void gameover() {
    printf("Game Over! You failed to overcome the challenges. Better luck next time!\n");
    exit(0);
}
