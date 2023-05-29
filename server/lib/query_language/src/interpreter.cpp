#include "interpreter.hpp"

interpreter::interpreter(){};

value interpreter::interpret(expr *expression, nlohmann::json card_) {
    card         = card_;
    value result = evaluate(expression);
    return result;
}

value interpreter::evaluate(expr *expression) {
    expression->accept(this);
    return result;
}

bool interpreter::is_truthy(value val) {
    if (val.val_type == EMPTY)
        return false;
    if (val.val_type == DOUBLE)
        return val.doub_val != 0;
    if (val.val_type == BOOL)
        return val.bool_val;
    return true;
}

bool interpreter::is_equal(value left, value right) {
    if (left.val_type == BOOL && right.val_type == BOOL)
        return left.bool_val == right.bool_val;
    if (left.val_type == DOUBLE && right.val_type == DOUBLE)
        return left.doub_val == right.doub_val;
    if (left.val_type == JSON && right.val_type == JSON)
        return left.json_val == right.json_val;
    if (left.val_type == EMPTY && right.val_type == EMPTY)
        return true;
    return false;
}


void interpreter::check_number_operand(value operand) {
    if (operand.val_type != tt::DOUBLE) {
        throw ComponentException("Invalid operand type");
    }
}

void interpreter::check_json_operand( value operand) {
    if (operand.val_type != tt::JSON) {
        throw ComponentException("Expected JSON");
    }
}

void interpreter::check_number_operands(token oper, value left, value right) {
    if (left.val_type != tt::DOUBLE || right.val_type != tt::DOUBLE) {
        throw ComponentException("Invalid operand type");
    }
    if (right.doub_val == 0 && oper.type == tt::SLASH) {
        throw ComponentException("Division by zero");
    }
}



void interpreter::visit(binary *expr) {
    value left  = evaluate(expr->get_leftptr());
    value right = evaluate(expr->get_rightptr());
    switch (expr->get_opername().type) {
        case PLUS:
            if (left.val_type == tt::DOUBLE && right.val_type == tt::DOUBLE) {
                result = value(left.doub_val + right.doub_val);
            } else if (left.val_type == tt::JSON && right.val_type == tt::JSON) {
                result = value(mergeJson(left.json_val, right.json_val));
            } else {
                throw ComponentException("Invalid operand type");
            }
            break;
        case MINUS:
            check_number_operands(expr->get_opername(), left, right);
            result = value(left.doub_val - right.doub_val);
            break;
        case STAR:
            check_number_operands(expr->get_opername(), left, right);
            result = value(left.doub_val * right.doub_val);
            break;
        case SLASH:
            check_number_operands(expr->get_opername(), left, right);
            result = value(left.doub_val / right.doub_val);
            break;
        case LESS:
            check_number_operands(expr->get_opername(), left, right);
            result = value(left.doub_val < right.doub_val);
            break;
        case LESS_EQUAL:
            check_number_operands(expr->get_opername(), left, right);
            result = value(left.doub_val <= right.doub_val);
            break;
        case GREATER:
            check_number_operands(expr->get_opername(), left, right);
            result = value(left.doub_val > right.doub_val);
            break;
        case GREATER_EQUAL:
            check_number_operands(expr->get_opername(), left, right);
            result = value(left.doub_val >= right.doub_val);
            break;
        case BANG_EQUAL:
            check_number_operands(expr->get_opername(), left, right);
            result = value(!is_equal(left, right));
            break;
        case EQUAL_EQUAL:
            check_number_operands(expr->get_opername(), left, right);
            result = value(is_equal(left, right));
            break;
        default:
            throw ComponentException("Invalid operand type");
            break;
    }
}

void interpreter::visit(grouping *expr) {
    expr->get_expr()->accept(this);
}

void interpreter::visit(func_in *expr) {
    value left  = evaluate(expr->get_leftptr());
    value right = evaluate(expr->get_rightptr());
    if (left.val_type == STRING && right.val_type == JSON) {
        result = value(find_word_inJson(left.str_val, right.json_val));
    } else {
        result = value(false);
    }
}


void interpreter::visit(unary *expr) {
    value right = evaluate(expr->get_expr());

    switch (expr->get_opername().type) {
        case tt::MINUS:
            check_number_operand(right);
            result = value(-right.doub_val);
            break;
        case tt::NOT:
            result = value(!is_truthy(right));
            break;
        case tt::LEN:
            check_json_operand(right);
            result = value(json_length(right.json_val));
            break;
        case tt::SPLIT:
            check_json_operand(right);
            result = value(splitJson(right.json_val));
            break;
        case tt::UPPER:
            check_json_operand(right);
            result = value(upperJsonString(right.json_val));
            break;
        case tt::LOWER:
            check_json_operand(right);
            result = value(lowerJsonString(right.json_val));
            break;
        case tt::REDUCE:
            check_json_operand(right);
            result = value(reduceJson(right.json_val));
            break;
        default:
            ComponentException("Invalid operand type");
            break;
    }
}


nlohmann::json interpreter::upperJsonString(const nlohmann::json &data) {
    
    if (data.is_string()) {
        std::string str = data.get<std::string>();
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        return str;
    }

    if (data.is_array()) {
        nlohmann::json result = nlohmann::json::array();
        for (const auto &item : data) {
            result.push_back(upperJsonString(item));
        }
        return result;
    }

    return nlohmann::json();
    // exeption?
}


nlohmann::json interpreter::lowerJsonString(const nlohmann::json &data) {
    
    if (data.is_string()) {
        std::string str = data.get<std::string>();
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }
    
    if (data.is_array()) {
        nlohmann::json result = nlohmann::json::array();
        for (const auto &item : data) {
            result.push_back(lowerJsonString(item));
        }
        return result;
    }

    return nlohmann::json();
    
}

std::vector<std::string> interpreter::splitString(const std::string &str) {
    std::vector<std::string> words;
    std::string              word;
    std::istringstream       iss(str);
    while (iss >> word) {
        words.push_back(word);
    }
    return words;
}

// Рекурсивная функция для разделения JSON элемента
nlohmann::json interpreter::splitJson(const nlohmann::json &jsonValue) {
    if (jsonValue.is_null()) {
        return nlohmann::json::array();
    }

    if (jsonValue.is_string()) {
        std::string str = jsonValue.get<std::string>();
        return splitString(str);
    }

    if (jsonValue.is_array()) {
        nlohmann::json result = nlohmann::json::array();
        for (const auto &item : jsonValue) {
            if (item.is_string()) {
                std::string str = item.get<std::string>();
                result.push_back(splitString(str));
            }
        }
        return result;
    }

    return nlohmann::json::array();
}

double interpreter::json_length(const nlohmann::json &jsonValue) {
    if (jsonValue.is_null()) {
        return 0;
    }

    if (jsonValue.is_array() || jsonValue.is_object()) {
        return jsonValue.size();
    }

    return 1; // неитерируемый объект, например число или строка
}

void interpreter::visit(literal *expr) {
    if (!expr->get_json_namevec().empty()) {

        nlohmann::json json_val = find_json_value(card, expr->get_json_namevec());
        if (!json_val.empty()) {
            expr->get_value().val_type = JSON;
            expr->get_value().json_val = json_val;
        } else {
            expr->get_value().val_type = EMPTY;
        }
    }
    result = expr->get_value();
}


bool interpreter::find_word_inJson(std::string word, nlohmann::json jsonValue) {
    if (jsonValue.is_string()) {
        return jsonValue.get<std::string>() == word;
    }

    if (!jsonValue.is_array()) {
        return false;
    }
    for (const auto &element : jsonValue) {
        if (find_word_inJson(word, element)) {
            return true;
        }  
    }
    return false;
}




nlohmann::json interpreter::find_json_value(const nlohmann::json& card,
                                            std::vector<std::string> levels_vec) {
    nlohmann::json current_json = card;

    for (size_t i = 0; i < levels_vec.size(); ++i) {
        std::string key = levels_vec[i];

        if (current_json.is_object()) {
            if (current_json.contains(key)) {
                current_json = current_json[key];
            } else if (key == "$ANY") {
                return handleAnyKey(current_json, levels_vec, i);
            } else if (key == "$SELF") {
                return getSelfKeys(current_json);
            } else {
                return nlohmann::json();
            }
        } else {
            return nlohmann::json();
        }
    }

    return current_json;
}

nlohmann::json interpreter::handleAnyKey(const nlohmann::json& json_value,
                                         const std::vector<std::string>& levels_vec,
                                         size_t current_index) {
    nlohmann::json any_values;

    for (auto it = json_value.begin(); it != json_value.end(); ++it) {
        const auto& result = find_json_value(
            it.value(),
            std::vector<std::string>(levels_vec.begin() + current_index + 1, levels_vec.end())
        );

        if (!result.is_null()) {
            any_values.push_back(result);
        }
    }

    if (any_values.size() == 1) { // возвращаем элемент, а не массив
        return any_values[0];
    } else {
        return any_values;
    }
}

nlohmann::json interpreter::getSelfKeys(const nlohmann::json& json_value) {
    nlohmann::json self_keys;

    for (auto it = json_value.begin(); it != json_value.end(); ++it) {
        self_keys.push_back(it.key());
    }

    return self_keys;
}



void interpreter::visit(logical_expr *ex) {
    value left = evaluate(ex->get_leftptr());
    if (ex->get_opername().type == OR) {
        if (is_truthy(left)) {
            result = left;
            return;
        }
    } else {
        if (!is_truthy(left)) {
            result = left;
            return;
        }
    }
    result = evaluate(ex->get_rightptr());
}

nlohmann::json interpreter::reduceJson(const nlohmann::json &jsonElem) {
    if (jsonElem.is_null()) {
        return nlohmann::json();
    }

    nlohmann::json result;

    for (const auto &item : jsonElem) {
        if (item.is_array()) {
            for (const auto &nestedItem : item) {
                result.push_back(nestedItem);
            }
        } else {
            result.push_back(item);
        }
    }

    return result;
}

nlohmann::json interpreter::mergeJson(const nlohmann::json &jsonLeft,
                                      const nlohmann::json &jsonRight) {
    nlohmann::json mergedJson = nlohmann::json::object();

    for (nlohmann::json::const_iterator it = jsonLeft.begin(); it != jsonLeft.end();
         ++it) {
        mergedJson[it.key()] = it.value();
    }
    for (nlohmann::json::const_iterator it = jsonRight.begin(); it != jsonRight.end();
         ++it) {
        mergedJson[it.key()] = it.value();
    }
    return mergedJson;
}
