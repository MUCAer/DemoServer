#include "google/protobuf/message.h"
#include "gtest/gtest.h"
#include "yaml-cpp/yaml.h"
#include "mysql.h"
#include "util/tc_mysql.h"
#include <string>
#include <iostream>
#include <memory>
#include <cstdint>
/**
 * @class DemoServerTest
 * @desc 测试DemoServer环境初始化类
 */
class DemoServerTest : public testing::Environment {
public:
    /* init test environment. */
    virtual void SetUp() {};

    /* clear test environment. */
    virtual void TearDown() {}; 
};

/*
 * @class TestDictManager
 */
class TestDict : public testing::Test {
public:
    /* start test. */
    static void SetUpTestCace() {
        std::cout << "StartDictTesting." << std::endl;
    }
    
    /* end test. */
    static void TearDownTestCase() {
        std::cout << "TearDownDictTesting." << std::endl;
    }

};


TEST_F(TestDict, test_gtest)  {
    ASSERT_EQ(1, 1);
}

// TEST_F(TestDict,  test_parser_manager) {
//    std::shared_ptr<gcs::parser::MessageParserManager> msg_manager_ptr = std::make_shared<gcs::parser::MessageParserManager>();
//    /* test none-exist key. */
//    gcs::parser::parser_func_t msg_parser =  msg_manager_ptr->get_parser_func("empty_key");
//    EXPECT_EQ(msg_parser, nullptr);

// }
const std::string DB_CONF = "../conf/config.yaml";
int main(int argc, char* argv[]) {
    testing::AddGlobalTestEnvironment(new DemoServerTest);
    testing::InitGoogleTest(&argc, argv);
    printf("hello world\n");
    std::cout << "this code is only for test yaml" << std::endl;

    /* Node conf. */
    YAML::Node conf = YAML::LoadFile(DB_CONF);
    
    /*----------------------------------- display db_config ----------------------------------------*/
    std::cout << "Database:"<< std::endl;
    std::cout << "domain:  " << conf["custom_db"]["db_domain"].as<std::string>() << std::endl;
    std::cout << "username:" << conf["custom_db"]["db_username"].as<std::string>() << std::endl;
    std::cout << "passwd:  " << conf["custom_db"]["db_passwd"].as<std::string>() << std::endl;
    std::cout << "schema:  " << conf["custom_db"]["db_schema"].as<std::string>() << std::endl;

    /*----------------------------------- display redis ----------------------------------------*/
    std::cout << "Redis" << std::endl;
    std::cout << "redis_domain: " << conf["redis"]["redis_domain"].as<std::string>() << std::endl;
    std::cout << "redis_passwd: " << conf["redis"]["redis_passwd"].as<std::string>() << std::endl;
    tars::TC_Mysql _mysqlConfig;
    /*----------------------------------- display hello ----------------------------------------*/
    std::cout << "HelloServer" << std::endl;
    
    /* vector of name string. */
    std::vector<std::string> name_vec = conf["hello"]["num_config"].as<std::vector<std::string> >();
    if(!name_vec.empty())
      std::cout << name_vec[0] << std::endl;

    return RUN_ALL_TESTS();
}
