#ifndef WORDPLUGINWRAPPER_H
#define WORDPLUGINWRAPPER_H

#include <memory>
#include <string>
#include <vector>

#include "../Card.h"
#include "../interfaces/IWordPluginWrapper.h"
#include "BasicPluginWrapper.h"

class WordPluginWrapper : public BasicPluginWrapper,
                          virtual public IWordPluginWrapper {
 public:
    WordPluginWrapper(std::shared_ptr<IRequestable> connection);
    std::pair<std::vector<Card>, std::string>
                                        get(const std::string &word,
                                            const std::string &query,
                                            size_t             batch_size) override;
    std::pair<std::string, std::string> get_dict_scheme() override;
};

#endif  // WORDPLUGINWRAPPER_H