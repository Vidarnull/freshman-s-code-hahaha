#include <stdio.h>   // 标准输入输出
#include <stdlib.h>  // 内存分配，exit()
#include <string.h>  // 字符串操作
#include <stdbool.h> // 使用bool类型

// --- 1. 常量和结构体定义 ---
#define MAX_STUDENTS 100         // 最大学生数量
#define FILENAME "students_data.txt" // 数据存储文件名

// 定义学生信息的结构体
typedef struct {
    int id;               // 学号
    char name[20];        // 姓名 (不含空格)
    char major[30];       // 专业 (不含空格)
    float score;          // C语言成绩
} Student;

// --- 2. 全局变量 ---
Student students[MAX_STUDENTS];
int student_count = 0; // 当前学生数量

// --- 3. 文件操作模块 ---

/**
 * @brief 从文件加载学生数据到内存数组。
 */
void load_data() {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        printf("\n> 提示：数据文件 '%s' 不存在或无法打开，将创建新文件。\n", FILENAME);
        student_count = 0;
        return;
    }

    student_count = 0;
    // 使用fscanf按格式读取结构体数据
    while (student_count < MAX_STUDENTS && 
           fscanf(fp, "%d %s %s %f", 
                  &students[student_count].id, 
                  students[student_count].name, 
                  students[student_count].major, 
                  &students[student_count].score) == 4) {
        student_count++;
    }

    fclose(fp);
    printf("\n> 系统启动成功，已加载 %d 条学生记录。\n", student_count);
}

/**
 * @brief 将内存中的学生数据保存到文件。
 */
void save_data() {
    FILE *fp = fopen(FILENAME, "w"); // 使用 'w' 模式覆盖写入
    if (fp == NULL) {
        printf("\n> 错误：无法打开数据文件 '%s' 进行写入！\n", FILENAME);
        return;
    }

    // 逐个写入学生结构体数据
    for (int i = 0; i < student_count; i++) {
        fprintf(fp, "%d %s %s %.2f\n", 
                students[i].id, 
                students[i].name, 
                students[i].major, 
                students[i].score);
    }

    fclose(fp);
    printf("\n> 成功保存 %d 条学生记录到文件 '%s'。\n", student_count, FILENAME);
}

// --- 4. 核心功能模块 ---

/**
 * @brief 显示系统主菜单。
 */
void show_menu() {
    printf("\n--- 🎓 简易学生信息管理系统 (V1.0) ---\n");
    printf(" 1. 添加学生信息\n");
    printf(" 2. 显示所有学生信息\n");
    printf(" 3. 查找学生信息 (按学号)\n");
    printf(" 4. 删除学生信息 (按学号)\n");
    printf(" 5. 排序学生信息 (按学号升序)\n");
    printf(" 6. 保存数据并退出系统\n");
    printf("--------------------------------------\n");
    printf("请选择操作 (1-6): ");
}

/**
 * @brief 添加新的学生记录。
 */
void add_student() {
    if (student_count >= MAX_STUDENTS) {
        printf("\n> 错误：系统容量已满，无法添加更多学生！\n");
        return;
    }

    Student s;
    printf("\n--- 添加学生 ---\n");
    printf("请输入学号: ");
    scanf("%d", &s.id);
    printf("请输入姓名 (无空格): ");
    scanf("%s", s.name);
    printf("请输入专业 (无空格): ");
    scanf("%s", s.major);
    printf("请输入C语言成绩: ");
    scanf("%f", &s.score);
    
    // 将新学生添加到数组中
    students[student_count] = s;
    student_count++;
    printf("\n> 成功添加学生: %s (学号: %d)\n", s.name, s.id);
}

/**
 * @brief 显示当前所有学生信息。
 */
void display_all_students() {
    if (student_count == 0) {
        printf("\n> 提示：当前系统中无任何学生记录。\n");
        return;
    }

    printf("\n--- 所有学生信息 (%d 条) ---\n", student_count);
    printf("学号\t姓名\t专业\t\t成绩\n");
    printf("--------------------------------------\n");
    for (int i = 0; i < student_count; i++) {
        printf("%d\t%s\t%s\t\t%.2f\n", 
               students[i].id, 
               students[i].name, 
               students[i].major, 
               students[i].score);
    }
    printf("--------------------------------------\n");
}

/**
 * @brief 查找学生信息（按学号）。
 */
void search_student() {
    int id_to_find;
    printf("\n--- 查找学生 (按学号) ---\n");
    printf("请输入要查找的学号: ");
    scanf("%d", &id_to_find);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id_to_find) {
            printf("\n> 找到学生：\n");
            printf("学号: %d\n姓名: %s\n专业: %s\n成绩: %.2f\n", 
                   students[i].id, 
                   students[i].name, 
                   students[i].major, 
                   students[i].score);
            return;
        }
    }
    printf("\n> 未找到学号为 %d 的学生记录。\n", id_to_find);
}

/**
 * @brief 删除学生信息（按学号）。
 */
void delete_student() {
    int id_to_delete;
    printf("\n--- 删除学生 (按学号) ---\n");
    printf("请输入要删除的学号: ");
    scanf("%d", &id_to_delete);

    for (int i = 0; i < student_count; i++) {
        if (students[i].id == id_to_delete) {
            // 将后面的元素向前移动覆盖掉当前元素，实现删除操作
            for (int j = i; j < student_count - 1; j++) {
                students[j] = students[j + 1];
            }
            student_count--;
            printf("\n> 成功删除学号为 %d 的学生记录。\n", id_to_delete);
            return;
        }
    }
    printf("\n> 未找到学号为 %d 的学生记录，无法删除。\n", id_to_delete);
}

/**
 * @brief 对学生记录进行排序（按学号升序，使用冒泡排序）。
 */
void sort_students() {
    Student temp;
    bool swapped;
    
    // 冒泡排序
    for (int i = 0; i < student_count - 1; i++) {
        swapped = false;
        for (int j = 0; j < student_count - 1 - i; j++) {
            if (students[j].id > students[j+1].id) {
                // 交换结构体
                temp = students[j];
                students[j] = students[j+1];
                students[j+1] = temp;
                swapped = true;
            }
        }
        if (!swapped) break; // 如果一轮没有发生交换，说明已排序完成
    }
    printf("\n> 所有学生信息已按学号升序排序完成。\n");
}

// --- 5. 主函数 ---

int main() {
    int choice;
    
    // 启动时加载数据 (满足要求3：下次程序启动，从文件读入数据)
    load_data(); 

    while (1) {
        show_menu();
        
        // 读取用户输入的选择
        if (scanf("%d", &choice) != 1) {
            printf("\n> 输入无效，请输入数字。\n");
            // 清空输入缓冲区，防止输入错误导致无限循环
            while (getchar() != '\n'); 
            continue;
        }

        switch (choice) {
            case 1:
                add_student();
                break;
            case 2:
                display_all_students();
                break;
            case 3:
                search_student();
                break;
            case 4:
                delete_student();
                break;
            case 5:
                sort_students();
                break;
            case 6:
                // 退出时保存数据 (满足要求3：要求程序退出时，数据保存到文件)
                save_data(); 
                printf("\n--- 系统已退出。感谢使用！---\n");
                return 0; // 退出程序
            default:
                printf("\n> 无效的选择，请重新输入 1 到 6 之间的数字。\n");
        }
        
        // 增加暂停，提高用户体验
        printf("\n【按 Enter 键返回主菜单...】");
        // 清空输入缓冲区并等待用户按 Enter 键
        while (getchar() != '\n');
        getchar();
    }
}