/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperroch <gperroch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/29 12:04:15 by gperroch          #+#    #+#             */
/*   Updated: 2017/09/29 17:21:19 by gperroch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
#define NM_H

typedef struct				s_symbol_display
{
	long int				value;
	char					type;
	char					*name;
	struct s_symbol_display	*next;
	struct s_symbol_display	*previous;
} t_symbol_display;
void					sort_list_symbols(t_symbol_display **list);
int				ft_mapping_file(char *file_name, void **file_content,
	struct stat *stats);
void			ft_display_header(struct mach_header_64 *header);
void			ft_display_load_command(struct load_command *load_command, int ncmds);
void			dump_mem(void *ptr, int len, int col, char *name);
char			*load_command_type(uint32_t cmd);
void			display_load_symtab(struct load_command *load_command);
void			display_load_dysymtab(struct load_command *load_command);
void			test_strtab(char *ptr, int size);
char			find_section(void *header, int section_number);
void				display_symbols(t_symbol_display *list);
void						init_element(t_symbol_display **list, t_symbol_display **ptr);
void						set_element(t_symbol_display **ptr, struct nlist_64 *nlist, struct mach_header_64 *header, void *strtab);

void					listing_symbols(struct load_command *tmp_load_command, t_symbol_display **list, struct mach_header_64 *header, int i);

#endif
