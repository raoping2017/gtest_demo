#include <gtest/gtest.h>
#include <atomic>
#include <memory>

class ConfigSwitch {
public:
  ConfigSwitch(): valid_(0){}
  ~ConfigSwitch();

private:
  std::atomic<int> valid_;
  long begin_config_time_;
};

TEST(example, Newtest) {
  int* ptr = new int[5];
  double* ptr1;
  if(ptr){
    delete ptr;
    std::cout << "delete ptr" << std::endl;
  }

  if(ptr){
    std::cout << "===================== ptr not null" << std::endl;
    ptr1 = new double[3];
  } else
    std::cout << "===================== ptr null" << std::endl;
}

TEST(example, doubleInttest) {
  double d1 = 223372036854775807;
  int v1 = (int)d1;
  std::cout << v1 << std::endl;
}

TEST(example, maptest) {
  std::map<std::string, int> map1;
  map1["1"] = 1; 
  map1["2"] = 2; 
  map1["3"] = 3; 
  for(auto& it: map1){
    std::cout << it.first << std::endl;
  }
}

std::string GetSingleLine(const std::string& str) {
  std::string temp = "";
  for(int i=0; i<str.size(); i++){
    if(str[i] == '\n')
      temp += ' ';
    else
      temp += str[i];
  }
  return temp;
}

TEST(example, GetSingleLinetest) {
  std::string str = " select * from testtable a57 where 1=1\nlimit 0, 200";
  std::string str1 = GetSingleLine(str);
  std::cout << str1 << std::endl;
}

TEST(example, mapretest) {

  int max = 50;
  std::vector<int64_t> v_expr_index_to_rule_postion_;
  v_expr_index_to_rule_postion_.reserve(max);
  v_expr_index_to_rule_postion_.resize(max);

  int len = 1000;
  for(int i=0; i<len; i++){
    v_expr_index_to_rule_postion_[i] = i;
  }

  v_expr_index_to_rule_postion_.clear();

  std::cout << v_expr_index_to_rule_postion_[50] << std::endl;
}

TEST(example, mapre1test) {

  int max = 50;
  std::vector<int64_t> v_expr_index_to_rule_postion_;
  v_expr_index_to_rule_postion_.reserve(max);
  //v_expr_index_to_rule_postion_.resize(max);

  int len = 100;
  for(int i=0; i<len; i++){
    //v_expr_index_to_rule_postion_[i] = i;
    v_expr_index_to_rule_postion_.push_back(i);
  }

  std::cout << v_expr_index_to_rule_postion_.size() << std::endl;

  for(int i=0; i<v_expr_index_to_rule_postion_.size(); i++){
    std::cout << i << "======" << v_expr_index_to_rule_postion_[i] << std::endl;
  }

  //v_expr_index_to_rule_postion_.clear();
  std::cout << v_expr_index_to_rule_postion_[50] << std::endl;
  v_expr_index_to_rule_postion_.clear();

}

const uint8_t TagSymbol = '"';
const std::vector<uint8_t> tag_begin_ = {TagSymbol, TagSymbol, TagSymbol, TagSymbol};

TEST(example, tagtest) {
  std::cout << (char*)tag_begin_.data() << std::endl;
}

TEST(example, intstringtest) {
  uint8_t t1 = 1;
  std::cout << (char*)(&t1) << std::endl;
}

enum ValueType { VT_TEXT = 1, VT_OTHER };

ValueType GetSqlValueType(const std::string& sql_value) {
  if (sql_value != "" && (sql_value[0] == '"' || sql_value[0] == '\'')) {
    return VT_TEXT;
  }
  return VT_OTHER;
}

int ConvertSqlValueToString(const std::string& sql_value, std::string* new_string) {
  if (GetSqlValueType(sql_value) != VT_TEXT) {
    *new_string = "";
    return -1;
  }
  new_string->assign(sql_value.substr(1, sql_value.size() - 2));
  return 0;
}

int ConvertStringToSqlValue(const std::string& str, std::string* sql_value) {
  if (!sql_value || str == "") return -1;

  const std::string hex = "0123456789ABCDEF";
  sql_value->clear();
  sql_value->push_back('\'');
  for (int i = 0; i < (int)str.size(); ++i) {
    const char ch = str[i];
    sql_value->push_back(hex[(ch & 0xF0) >> 4]);
    sql_value->push_back(hex[ch & 0xF]);
  }
  sql_value->push_back('\'');
  return 0;
}

static int ConvertHexToBytes(const std::vector<uint8_t>& hex_str, std::vector<uint8_t>* bytes) {
  // static int ConvertHexToBytes(const std::string& hex_str, std::vector<uint8_t>* bytes) {
  const char* hex_data = (char*)hex_str.data();
  int hex_size = (int)hex_str.size();
  bytes->reserve(hex_size / 2);
  bytes->resize(hex_size / 2);
  uint8_t* byte_data = bytes->data();

  for (int i = 0; i < hex_size / 2; i++) {
    sscanf(hex_data + i * 2, "%02hhX", byte_data + i);
  }
  return 0;
}

using ByteBuffer = std::vector<uint8_t>;

ByteBuffer string_to_bytebuffer(std::string str) {
  ByteBuffer v_str;
  v_str.assign(str.begin(), str.end());
  return v_str;
}

std::string bytebuffer_to_string(ByteBuffer v_str) {
  std::string str;  // std::string str = (char*)v_str.data();
  str.assign(v_str.begin(), v_str.end());
  return str;
}

TEST(example, intstring1test) {
  std::string str = {(char*)tag_begin_.data(), tag_begin_.size()};
  std::cout << str << std::endl;
  std::string str1;
  ConvertStringToSqlValue(str, &str1);
  std::cout << str1 << std::endl;

  std::string old_str;
  ConvertSqlValueToString(str1, &old_str);
  std::cout << old_str << std::endl;

  ByteBuffer bb_old_str = string_to_bytebuffer(old_str);
  ByteBuffer bb_old_str1;
  ConvertHexToBytes(bb_old_str, &bb_old_str1);

  std::string orgin_str = bytebuffer_to_string(bb_old_str1);
  std::cout << orgin_str << std::endl;
}

TEST(example, string1test) {
  std::string str;
  str.push_back('\'');
  str.append("dfdfdf");
  std::cout << str << std::endl;

  std::string str1 = "fdfdssadfdf";
  std::cout << str1.substr(1, 3) << std::endl;
}

TEST(example, string2test) {
  std::string str;
  str.push_back('\'');
  str.append("dfdfdf");
  std::cout << str << std::endl;

  std::string str1 = "fdfdssadfdf";
  std::cout << str1.substr(1, 3) << std::endl;
}

TEST(example, string3test) {
  std::string str;
  str.push_back('\'');
  str.append("dfdfdf");
  std::cout << str << std::endl;

  std::string str1 = "fdfdssadfdf";
  std::cout << str1.substr(1, 3) << std::endl;
}



