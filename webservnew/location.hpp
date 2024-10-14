/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bainur <bainur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:24:50 by bainur            #+#    #+#             */
/*   Updated: 2024/10/14 15:27:30 by bainur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include <cstdlib>
# include <fstream>
# include <iostream>
# include <map>
# include <sstream>
# include <string>
# include <unistd.h>
# include <vector>

class Location 
{
    public:
        Location();
        Location(const Location &copy);
        Location &operator=(const Location &copy);
        ~Location();
    private:
        std::string _path;
        std::string _root;
        std::string _index;
        std::map<short, std::string> _error_page;
        std::vector<std::string> _method;
        int _size_limit;
    
}
#endif