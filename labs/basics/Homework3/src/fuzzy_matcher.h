#pragma once
#include <QString>
#include <vector>
#include <algorithm>

namespace utils {
    inline int levenshtein(const QString &s1, const QString &s2) {
        int n = s1.size(), m = s2.size();
        std::vector<std::vector<int>> d(n + 1, std::vector<int>(m + 1));
        for (int i = 0; i <= n; ++i) d[i][0] = i;
        for (int j = 0; j <= m; ++j) d[0][j] = j;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                int cost = (s1[i - 1].toLower() == s2[j - 1].toLower()) ? 0 : 1;
                d[i][j] = std::min({d[i - 1][j] + 1, d[i][j - 1] + 1, d[i - 1][j - 1] + cost});
            }
        }
        return d[n][m];
    }
}