# 变量定义
CXX := g++
CXXFLAGS = -IHeader

# 目标定义
TARGET = test
SRC_DIR = src
HEAD_DIR = Header
SRC_FILES = $(SRC_DIR)/Observer.cpp
HEAD_FILES = $(HEAD_DIR)/Observer.h
OBJECTS = $(SRC_FILES:.cpp=.o)

# 最终生成目标
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# 编译.c文件为.o文件，-c表示只编译（生成.o）不链接（不生成可执行文件）
# $^当前所有依赖项，即$(SRC) $(HEADER)；$< 表示第一个依赖
# $@当前目标项
# g++ -IHeader src/SingleTon.cpp -o test亦可
%.o: %.cpp $(HEAD_FILES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	@./$(TARGET)
	