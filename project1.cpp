#include <iostream>


using namespace std;

enum enGameLevel { easy = 1, mid = 2, hard = 3, mix = 4 };
enum enOperationType { add = 1, sub = 2, multi = 3, divid = 4, mixx = 5 };

struct stQuestions {

	int number1 = 0, number2 = 0, courrectAns = 0, playerAns = 0;
	enGameLevel qGameLevel; enOperationType opType; bool finalResultes = false;

};

struct stQuizz {

	short numberOfQ = 0, numberOfRightAns = 0, numberofwrongAns = 0; bool pass = false;
	stQuestions listOfQue[100]; enGameLevel questionLevel; enOperationType opType;

};

string operationSympols(enOperationType enOperationSympols) {

	switch (enOperationSympols) {
	 case add:return "add(+)"; 
	 case sub: return "subtract(-)"; 
	 case multi: return "multiplication(*)"; 
	 case divid: return "divide(/)"; 	
	 default: return "mix(+, -, *, /)"; break;

	}
	
}

string questionLevel(enGameLevel queLevel) {

	string arrGameLevel[4]{ "essy","mid", "hard", "mix" };
	return arrGameLevel[(queLevel - 1)];

}

int randomNumbers(int from, int to) {

	return(rand() % (to - from + 1) + from); 

}

void setColor(bool rightAns)  {

	if (!rightAns) { 
		system("color 4F"); 
		cout << "\a"; 
	}
	else 
		system("color 2F");

}

short roundsGame() {

	short r = 0;
	do
	{
		cout << "Enter how many do you want to play [1-20] ?: ";
		cin >> r;

	} while ((r < 1) || (r > 20)); return r;
}

enGameLevel playerChooseLevel() {

	short c = 0;
	do
	{
		cout << "Enter a level to continue: 1-Esay, 2-Mid, 3-Hard, 4-Mix: ";
		cin >> c;

	} while ((c < 1) || (c > 4)); return((enGameLevel)c);
}

enOperationType playerChooseOp() {

	short c = 0;
	do
	{
		cout << "Enter operation type to play?: 1-add(+) , 2-sub(-), 3-multi(*), 4-divid(/) 5-mix(+, -, *, /): ";
		cin >> c;

	} while ((c < 1) || (c > 5)); return((enOperationType)c);

}

int claculte(int number1, int number2, enOperationType opType) {

	switch (opType) {
	 case enOperationType::add: return(number1 + number2);
	 case enOperationType::sub: return(number1 - number2);
	 case enOperationType::multi: return(number1 * number2);
	 case enOperationType::divid: return(number1 / number2);

	}
	return (enOperationType)opType;
}

enOperationType randomOperationType() {

	return((enOperationType)randomNumbers(1, 4));

}

stQuestions reGenerateQuestion(enOperationType opType, enGameLevel gameLevel) {

	stQuestions Q;
	if (opType == enGameLevel::mix) opType = randomOperationType();
	if (gameLevel == enOperationType::mixx) gameLevel = ((enGameLevel)randomNumbers(1, 4));

	Q.opType = opType;

	switch (gameLevel) {
	 case enGameLevel::easy:
		 Q.number1 = randomNumbers(5, 25);
		 Q.number2 = randomNumbers(5, 25);
		 Q.courrectAns = claculte(Q.number1, Q.number2, Q.opType);
		 Q.qGameLevel = gameLevel; return Q;
	 case enGameLevel::mid:
		 Q.number1 = randomNumbers(25, 50);
		 Q.number2 = randomNumbers(25, 50);
		 Q.courrectAns = claculte(Q.number1, Q.number2, Q.opType);
		 Q.qGameLevel = gameLevel; return Q;	
	 case enGameLevel::hard:
		 Q.number1 = randomNumbers(50, 75);
		 Q.number2 = randomNumbers(50, 75);
		 Q.courrectAns = claculte(Q.number1, Q.number2, Q.opType);
		 Q.qGameLevel = gameLevel; return Q;
	 default: break;
	}
	return Q;

}

void reGenerateQuizz(stQuizz& quizz) {

	for (short i = 0; i < quizz.numberOfQ; i++)
		quizz.listOfQue[i] = reGenerateQuestion(quizz.opType, quizz.questionLevel);

}

int playerAns() {

	int number = 0;
	cin >> number;
	return number;

}

void printQuestionList(stQuizz& quizz, short numberQ) {

	cout << "\nQuestion[" << (numberQ + 1) << '/' << quizz.numberOfQ << ']' << endl;
	cout << quizz.listOfQue[numberQ].number1 << endl;
	cout << quizz.listOfQue[numberQ].number2 << ' ';

	operationSympols(quizz.listOfQue[numberQ].opType); cout << "\n-------------------------" << endl;
}

void correctQuestionAns(stQuizz& quizz, short numberQ) {

	if ((quizz.listOfQue[numberQ].playerAns != quizz.listOfQue[numberQ].courrectAns)) {
		quizz.listOfQue[numberQ].finalResultes = false; quizz.numberofwrongAns = (quizz.numberofwrongAns + 1);
		cout << ">Wrong answer: " << endl; cout << ">Right answer: " << quizz.listOfQue[numberQ].courrectAns << endl;
	}
	else {
		quizz.listOfQue[numberQ].finalResultes = true; 
		quizz.numberOfRightAns = (quizz.numberOfRightAns + 1); cout << ">Right answer" << endl;
	}
	cout << endl;
	setColor(quizz.listOfQue[numberQ].finalResultes);
}

void askCorrectAnsListQ(stQuizz& quizz) {

	for (short c = 0; c < quizz.numberOfQ; c++) {
		printQuestionList(quizz, c);
		quizz.listOfQue[c].playerAns = playerAns();
		correctQuestionAns(quizz, c);
	}
	quizz.pass = (quizz.numberOfRightAns > quizz.numberofwrongAns);
}

string finalResults(bool pass) {

	if (pass)
		return "Pass\n";
	else
		return "Fail\n";
	
}

void printQuizzResults(stQuizz& quizz) {

	cout << "\n----------------------\n\n";
	cout << "      Final Results: " << finalResults(quizz.pass);
	cout << "\n----------------------\n\n";
	cout << "Number of question:" << quizz.numberOfQ << endl;
	cout << "Question level    :" << questionLevel(quizz.questionLevel) << endl;
	cout << "Operation Type	   :" << operationSympols(quizz.opType) << endl;
	cout << "Right answer	   :" << quizz.numberOfRightAns << endl;
	cout << "Wrong answer	   :" << quizz.numberofwrongAns << endl;
	cout << "----------------------\n";
}

void play() {

	stQuizz Q;
	Q.numberOfQ = roundsGame();
	Q.questionLevel = playerChooseLevel();
	Q.opType = playerChooseOp();

	reGenerateQuizz(Q);
	askCorrectAnsListQ(Q);
	printQuizzResults(Q);
}

void reSetScreen() {

	system("cls"); system("color 0F");
}

void start() {

	char c = 'Y';
	do {
		reSetScreen();
		play();
		cout << "Do you want to play again?: "; cin >> c; cout << endl;
	} while ((c == 'Y') || (c == 'y'));
}

int main(int argc, const char* argv[]) {

	srand((unsigned)time(NULL)); start();

	system("pause");
	return 0;
}