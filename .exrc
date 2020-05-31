if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
imap <Nul> <C-Space>
inoremap <expr> <Up> pumvisible() ? "\" : "\<Up>"
inoremap <expr> <S-Tab> pumvisible() ? "\" : "\<S-Tab>"
inoremap <expr> <Down> pumvisible() ? "\" : "\<Down>"
inoremap <silent> <Plug>(complete_parameter#overload_up) :call cmp#overload_next(0)
inoremap <silent> <Plug>(complete_parameter#overload_down) :call cmp#overload_next(1)
inoremap <silent> <Plug>(complete_parameter#goto_previous_parameter) :call cmp#goto_next_param(0)
inoremap <silent> <Plug>(complete_parameter#goto_next_parameter) :call cmp#goto_next_param(1)
imap <C-K> <Plug>(complete_parameter#goto_previous_parameter)
imap <C-J> <Plug>(complete_parameter#goto_next_parameter)
map <NL> :YcmCompleter GoToImprecise
smap  <Plug>(complete_parameter#goto_previous_parameter)
nnoremap ,d :YcmShowDetailedDiagnostic
nnoremap <silent> ,F :FZF /
nnoremap <silent> ,f :FZF
nnoremap ,  :nohlsearch
vmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
vnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(netrw#GX(),netrw#CheckIfRemote(netrw#GX()))
snoremap <silent> <Plug>(complete_parameter#overload_up) :call cmp#overload_next(0)
nnoremap <silent> <Plug>(complete_parameter#overload_up) :call cmp#overload_next(0)
snoremap <silent> <Plug>(complete_parameter#overload_down) :call cmp#overload_next(1)
nnoremap <silent> <Plug>(complete_parameter#overload_down) :call cmp#overload_next(1)
snoremap <silent> <Plug>(complete_parameter#goto_previous_parameter) :call cmp#goto_next_param(0)
nnoremap <silent> <Plug>(complete_parameter#goto_previous_parameter) :call cmp#goto_next_param(0)
snoremap <silent> <Plug>(complete_parameter#goto_next_parameter) :call cmp#goto_next_param(1)
nnoremap <silent> <Plug>(complete_parameter#goto_next_parameter) :call cmp#goto_next_param(1)
map <F2> :ClangFormat
smap <C-K> <Plug>(complete_parameter#goto_previous_parameter)
map <C-J> :YcmCompleter GoToImprecise
inoremap <expr> 	 pumvisible() ? "\" : "\	"
imap <NL> <Plug>(complete_parameter#goto_next_parameter)
imap  <Plug>(complete_parameter#goto_previous_parameter)
let &cpo=s:cpo_save
unlet s:cpo_save
set autoindent
set autoread
set autowrite
set background=dark
set backspace=indent,eol,start
set backupdir=~/.cache/vim/backup//
set clipboard=unnamedplus
set completeopt=menuone
set cpoptions=aAceFsB
set directory=~/.cache/vim/swap//
set fileencodings=ucs-bom,utf-8,default,latin1
set helplang=en
set hidden
set hlsearch
set ignorecase
set incsearch
set lazyredraw
set mouse=a
set omnifunc=syntaxcomplete#Complete
set pyxversion=3
set ruler
set runtimepath=~/.vim,~/.vim/bundle/Vundle.vim,~/.vim/bundle/vim-colors-solarized,~/.vim/bundle/vim-clang-format,~/.vim/bundle/vim-cpp-enhanced-highlight,~/.vim/bundle/YouCompleteMe,~/.vim/bundle/CompleteParameter.vim,/usr/share/vim/vimfiles,/usr/share/vim/vim82,/usr/share/vim/vimfiles/after,~/.vim/after,~/.vim/bundle/Vundle.vim,~/.fzf,~/.vim/bundle/Vundle.vim/after,~/.vim/bundle/vim-colors-solarized/after,~/.vim/bundle/vim-clang-format/after,~/.vim/bundle/vim-cpp-enhanced-highlight/after,~/.vim/bundle/YouCompleteMe/after,~/.vim/bundle/CompleteParameter.vim/after
set shell=zsh
set shortmess=filnxtToOSc
set showcmd
set showmatch
set smartcase
set smartindent
set statusline=2
set suffixes=.bak,~,.o,.info,.swp,.aux,.bbl,.blg,.brf,.cb,.dvi,.idx,.ilg,.ind,.inx,.jpg,.log,.out,.png,.toc
set tabstop=4
set undodir=~/.cache/vim/undo//
set visualbell
set wildmenu
" vim: set ft=vim :
