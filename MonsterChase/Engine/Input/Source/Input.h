#ifndef INPUT_H
#define INPUT_H

namespace Engine
{
	class Input
	{
	public:
		Input();
		static void ResetState();
		static void MoveKeyCallback(unsigned int i_VKeyID, bool bWentDown);
		static void Read();
		static void ReadKey(char key);
		static bool IsDown(char key);

		static const char A = 'A';
		static const char D = 'D';
		static const char S = 'S';
		static const char W = 'W';

		static const char Q = 'Q';

	private:
		static bool isAdown;
		static bool isDdown;
		static bool isSdown;
		static bool isWdown;

		static bool isQDown;
	};
}

#endif // !INPUT_H
