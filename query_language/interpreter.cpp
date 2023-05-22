#include "interpreter.h"

interpreter::interpreter() {};

value interpreter::interpret(expr* expression, json card_) {
    card = card_;
    value result = evaluate(expression);
    return result;
}


value interpreter::evaluate( expr*  expression){
    expression->accept(this);
    return result;
}



bool interpreter::is_truthy(value val){
    if (val.val_type == EMPTY) return false;
    if (val.val_type == DOUBLE) return val.doub_val != 0;
    if (val.val_type == BOOL) return val.bool_val;
    return true;
}

bool interpreter::is_equal(value left, value right){
    if (left.val_type == BOOL && right.val_type == BOOL) return left.bool_val == right.bool_val;
    if (left.val_type == DOUBLE && right.val_type == DOUBLE) return left.doub_val == right.doub_val;
    if (left.val_type == JSON && right.val_type == JSON) return left.json_val == right.json_val;
    if (left.val_type == EMPTY && right.val_type == EMPTY) return true;
    return false;
}


/*void interpreter::check_number_operand(token oper, value operand){
    if (operand.val_type == DOUBLE) 
        return;
    // обработать ошибку 
}*/

/*void interpreter::check_number_operands(token oper, value left, value right){
    if (left.val_type == DOUBLE && right.val_type == DOUBLE){ 
        if (right.doub_val == 0 && oper.type == SLASH)
        //   обработать ошибку 
        return;
        }
    // обработать ошибку 
}*/

void interpreter::visit(binary* expr){
    value left = evaluate(expr->left.get());
    value right = evaluate(expr->right.get());
    switch(expr->op.type){
        case PLUS:
            if (left.val_type == DOUBLE && right.val_type == DOUBLE){
                result = value(left.doub_val + right.doub_val);
            } else if (left.val_type == DOUBLE && right.val_type == DOUBLE){
                result = value(mergeJson(left.json_val, right.json_val));

            }
                // обработать ошибку
            break;
        case MINUS:
            //проверить типы 
             if (left.val_type == DOUBLE && right.val_type == DOUBLE){
                result = value(left.doub_val - right.doub_val);
            }
            break;    
        case STAR:
            //check_number_operands(expr->op, left, right);
             if (left.val_type == DOUBLE && right.val_type == DOUBLE){
                result = value(left.doub_val * right.doub_val);
            }
            break;
        case SLASH:
            //check_number_operands(expr->op, left, right);
            result = value(left.doub_val / right.doub_val);
            break;    
        case LESS:
            //check_number_operands(expr->op, left, right);
            result = value(left.doub_val < right.doub_val);
            break;   
        case LESS_EQUAL:
            //check_number_operands(expr->op, left, right);
            result = value(left.doub_val <= right.doub_val);
            break; 
        case GREATER:
            //check_number_operands(expr->op, left, right);
            result = value(left.doub_val > right.doub_val);
            break;
        case GREATER_EQUAL:
            //check_number_operands(expr->op, left, right);
            result = value(left.doub_val >= right.doub_val);
            break;
        case BANG_EQUAL:
            result = value(!is_equal(left,right));
            break;
        case EQUAL_EQUAL:
            result = value(is_equal(left,right));
            break;
        default:
            result = value();
            break;
    }
}

void interpreter::visit(grouping* expr){
    expr->expression->accept(this);
}	


void interpreter::visit(func_in* expr){
    value left = evaluate(expr->left.get());
    value right = evaluate(expr->right.get());
    if (left.val_type == STRING && right.val_type == JSON){
        result = value(find_word_inJson(left.str_val, right.json_val));
    }
}	

bool interpreter::find_word_inJson(std::string word, json jsonValue){
    if (jsonValue.is_string()) {
        return jsonValue.get<std::string>() == word;
    } else if (jsonValue.is_array()) {
        for (const auto& element : jsonValue) {
            if (find_word_inJson(word, element)) {
                return true;
            }
        }
    } else {
        return false;
    }
}



void interpreter::visit( unary* expr){
    value right = evaluate(expr->ex.get());
    
    switch(expr->op.type){
        case tt::MINUS: 
            //check_number_operand(expr->op, right);
            result = value(-right.doub_val);
            break;
        case tt::NOT:
                result = value(!is_truthy(right));
            break;
        case tt::LEN:
            if (right.val_type == tt::JSON){
                
                result = value(json_length(right.json_val));
            } // обработать
            break;
        case tt::SPLIT:
            if (right.val_type == tt::JSON){

                result = value(splitJson(right.json_val));
            } // обработать
            break;
        case tt::UPPER:
            if (right.val_type == tt::JSON){

                result = value(upperJsonString(right.json_val));
            } // обработать
            break;
        case tt::LOWER:
            if (right.val_type == tt::JSON){

                result = value(lowerJsonString(right.json_val));
            } // обработать
            break;
        case tt::REDUCE:
            if (right.val_type == tt::JSON){

                result = value(reduceJson(right.json_val));
            } // обработать
            break;
        default:
            result = value();
            break;
    }
}

// нужно добавить русские символы 
json interpreter::upperJsonString(const json& data)
{
    if (data.is_array()) {
        json result = json::array();
        
        for (const auto& item : data) {
            result.push_back(upperJsonString(item));  
        }
        
        return result;
    } else if (data.is_string()) {
        std::string str = data.get<std::string>();
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        return str;
    } else {
        return json();  
    }
}

json interpreter::lowerJsonString(const json& data)
{
    if (data.is_array()) {
        json result = json::array();
        
        for (const auto& item : data) {
            result.push_back(lowerJsonString(item));  
        }
        
        return result;
    } else if (data.is_string()) {
        std::string str = data.get<std::string>();
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    } else {
        return json();  
    }
}



std::vector<std::string> interpreter::splitString(const std::string& str) {
    std::vector<std::string> words;
    std::string word;
    std::istringstream iss(str);
    while (iss >> word) {
        words.push_back(word);
    }
    return words;
}

// Рекурсивная функция для разделения JSON элемента
json interpreter::splitJson(const json& jsonValue) {
    if (jsonValue.is_null()) {
        return json::array();
    } else if (jsonValue.is_string()) {
        std::string str = jsonValue.get<std::string>();
        return splitString(str);
    } else if (jsonValue.is_array()) {
        json result = json::array();
        for (const auto& item : jsonValue) {
            if (item.is_string()) {
                std::string str = item.get<std::string>();
                result.push_back(splitString(str));
            }
        }
        return result;
    } else {
        return json::array();
    }
}


double interpreter::json_length(const json& jsonValue){
    if (jsonValue.is_null()) {
        return 0;
    } else if (jsonValue.is_array() || jsonValue.is_object()) {
        return jsonValue.size();
    } else {
        return 1; // объект неитерируемый
    }

}


void interpreter::visit(literal* expr){
    if (!expr->json_namevec.empty()){

       /* for (int i = 0; i < expr->json_namevec.size(); ++i ){
            std::cout << expr->json_namevec[i] <<" "<< i << std::endl;
        }*/

        json json_val= find_json_value(card, expr->json_namevec);
        if (!json_val.empty()){
            expr->val.val_type = JSON;
            expr->val.json_val = json_val;
        }
    }
    result = expr->val; 
}

// разбить на мелкие функции
json interpreter::find_json_value(const json& card, std::vector<std::string> levels_vec){
    json current_json = card;

    for (size_t i = 0; i < levels_vec.size(); ++i) {
        std::string key = levels_vec[i];

            if (current_json.is_object()){
                 if(current_json.contains(key)) {
                    current_json = current_json[key];
                } else if (key == "$ANY"){
                    json any_values;
                     for (auto it = current_json.begin(); it != current_json.end(); ++it) {
                        const auto& result = find_json_value(it.value(), std::vector<std::string>(levels_vec.begin() + i + 1, levels_vec.end()));
                        if (!result.is_null()) {
                            any_values.push_back(result);
                        }
                     }

                     if(any_values.size() == 1){
                        return any_values[0];
                     } else {
                        return any_values;
                     }

                } else if (key == "$SELF"){
                    json self_keys;
                    for (auto it = current_json.begin(); it != current_json.end(); ++it) {
                        self_keys.push_back(it.key());
                    }
                    return self_keys;
                } else {
                    return json();
                }
        } else {
            return json();
        }
    }
    return current_json;
}




void interpreter::visit(logical_expr* ex){
    value left = evaluate(ex->left.get());
    if (ex->oper.type == OR){
        if (is_truthy(left)){
            result = left;
            return;
        } 
    }
    else{
        if (!is_truthy(left)){
            result = left;
            return;
        }
    }
    result = evaluate(ex->right.get());
}

json interpreter::reduceJson(const json& jsonElem) {
    if (jsonElem.is_null()) {
        return json();  
    }
    
    json result;
    
    for (const auto& item : jsonElem) {
        if (item.is_array()) {
            for (const auto& nestedItem : item) {
                result.push_back(nestedItem);
            }
        } else {
            result.push_back(item);
        }
    }
    
    return result;
}


json interpreter:: mergeJson(const json& json1, const json& json2)
{
    json mergedJson = json::object();

    for (json::const_iterator it = json1.begin(); it != json1.end(); ++it) {
        mergedJson[it.key()] = it.value();
    }
    for (json::const_iterator it = json2.begin(); it != json2.end(); ++it) {
        mergedJson[it.key()] = it.value();
    }
    return mergedJson;
}
