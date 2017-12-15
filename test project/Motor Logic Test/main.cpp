#include "main.h";



int main() {
	cout << "test for motor logic" << endl;

	int startPos, endPos, desiredSpeed;
	string dummy;
	cout << "Set startpos:" << endl;
	cin >> startPos;
	cout << "Set the desired position" << endl;
	cin >> endPos;
	cout << "Set the moving speed" << endl;
	cin >> desiredSpeed;

	cout << "values are: " << endl << "\tstartpos: " << startPos << endl;
	cout << "\tendops: " << endPos << endl << "\tdesiredspeed: " << desiredSpeed << endl;

	cout << endl << "press enter to run the test" << endl << endl;
	cin.ignore();
	int positionsToMove = endPos - startPos;
	if (positionsToMove < 0) positionsToMove = positionsToMove *-1;
	setLogicValues(startPos, positionsToMove, desiredSpeed);
	endPos += 10;

	double speed = 0;
	if (endPos > startPos) {
		for (int i = startPos; i < endPos; i++) {
			double newSpeed = speed;
			calculateSpeed(i, newSpeed);

			cout << "pos:   " << i << " \tnewspeed: " << roundf(newSpeed * 100)/100 << "   \tdelta acceleration: " << roundf((newSpeed - speed)*100)/100 << endl;
			speed = newSpeed;
			//Sleep(1000);
		}
	}
	else {
		for (int i = startPos; i > endPos; i--) {
			double newSpeed = speed;
			calculateSpeed(i, newSpeed);
			cout << "pos:   " << i << " \tnewspeed: " << roundf(newSpeed * 100)/100 << "   \tacceleration: " << roundf((newSpeed - speed)*100)/100 << endl;
			speed = newSpeed;
			//Sleep(1000);
		}
	}


	cout << "finished :)" << endl;
	cin.ignore();

	return 0;
}