#include <gtest/gtest.h>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

// Вспомогательная функция: запускает команду и возвращает код возврата
static int run_cmd(const std::string& cmd) {
    return std::system(cmd.c_str());
}

// Прочитать файл в строку
static std::string read_file(const fs::path& p) {
    std::ifstream in(p);
    std::ostringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

// Проверяет, что в отчёте встречается ожидаемая строка (подстрока)
static bool contains_substr(const std::string& text, const std::string& sub) {
    return text.find(sub) != std::string::npos;
}

TEST(Integration_CreatorReporter, CreatesReportAndContainsSalary) {
    // Имена файлов теста (относительные к рабочей директории, откуда запускаешь тест)
    const std::string binfile = "itest_emps.bin";
    const std::string reportfile = "itest_report.txt";

    // Удаляем старые тестовые файлы если есть
    if (fs::exists(binfile)) fs::remove(binfile);
    if (fs::exists(reportfile)) fs::remove(reportfile);

    // Подготовим команду для Creator: передаём имена и количество
    // Creator ожидает: Creator <имя_файла> <количество>
    // Но Creator читает данные с stdin, поэтому воспользуемся here-doc подходом:
    // На Windows system() через cmd не поддерживает heredoc. Поэтому создаём временный input файл и перенаправим.
    // В этом тесте создадим input с двумя записей вручную: num name hours
    const std::string creator_input = "100\nIvan\n8.5\n200\nAnna\n10\n";
    const std::string input_txt = "itest_creator_input.txt";
    {
        std::ofstream in(input_txt);
        in << creator_input;
    }

    // Команда: перенаправляем stdin из файла
    // Обратите внимание: имя исполняемого должно быть доступно (Creator или Creator.exe)
    std::string creator_cmd = "Creator " + binfile + " 2 < " + input_txt;
    int rc = run_cmd(creator_cmd);
    EXPECT_EQ(rc, 0) << "Creator return code != 0. Command: " << creator_cmd;

    // Проверяем, что бинарник создан и имеет ненулевой размер
    ASSERT_TRUE(fs::exists(binfile));
    ASSERT_GT(fs::file_size(binfile), 0u);

    // Теперь запускаем Reporter: Reporter <бинарник> <отчёт.txt> <ставка>
    const double rate = 100.0;
    std::ostringstream runcmd;
    runcmd << "Reporter " << binfile << " " << reportfile << " " << rate;
    rc = run_cmd(runcmd.str());
    EXPECT_EQ(rc, 0) << "Reporter return code != 0. Command: " << runcmd.str();

    // Проверяем отчётный файл
    ASSERT_TRUE(fs::exists(reportfile));
    std::string report = read_file(reportfile);

    // Должны быть заголовки
    EXPECT_TRUE(contains_substr(report, "Отчёт по файлу")) << "Report header missing";

    // Проверяем, что для ID 100 и 200 есть зарплата (8.5*100 = 850.00, 10*100 = 1000.00)
    EXPECT_TRUE(contains_substr(report, "850")) << "Expected salary for ID 100 not found";
    EXPECT_TRUE(contains_substr(report, "1000")) << "Expected salary for ID 200 not found";

    // Убираем временные файлы
    fs::remove(input_txt);
    fs::remove(binfile);
    fs::remove(reportfile);
}
