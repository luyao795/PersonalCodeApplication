#ifndef VALIDITYERRORCHECKER_H
#define VALIDITYERRORCHECKER_H

namespace Engine
{
	bool CheckNaN(const float target);
	bool AreAboutEqual(const float left, const float right);
	bool AreAboutEqual(const float left, const float right, const float epsilon);
}

#endif // !VALIDITYERRORCHECKER_H
