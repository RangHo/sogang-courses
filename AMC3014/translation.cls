%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% MLA-compliant Article LaTeX Document Class
%% (Sogang University AMC3014 Variant)
%% Author: RangHo Lee <hello@rangho.me>
%%
%% A LaTeX document class that creates an MLA-formatted essay.
%% This document class already imports `biblatex` package with MLA formatting,
%% so the users of this package need not import such package again. Just provide
%% the author's name, professor name, course title, date, and essay title. The
%% title page and the works cited page will be provided by default.
%% One may use `\today` macro to automatically generate the date.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%% Document class identification %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\ProvidesClass{translation}[2024/03/05 v0.1.0 Variant of MLA format for Sogang University AMC3104 class]
\NeedsTeXFormat{LaTeX2e}
\LoadClass[11pt]{article}


%% Imported packages %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% American English style
\usepackage[american]{babel}

% Korean language support
\usepackage{kotex}

% Paper geometry settings
\usepackage{geometry}

% OpenType font handler (requires XeTeX or LuaTeX engine)
\usepackage{fontspec}

% Set document-wide spacing
\usepackage{setspace}

% Always indent after section
\usepackage{indentfirst}

% Date formatting helper
\usepackage{datetime2}

% Context-aware quotation helper
\usepackage{csquotes}

% Hyperlink helper
\usepackage{hyperref}

% BibLaTeX bibliography manager
\usepackage[backend=biber,style=mla]{biblatex}


%% Macro definitions %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% MLA header information (existing)
\renewcommand\date[1]{%
  \def\MLA@date{#1}%
}
\renewcommand\title[1]{%
  \def\MLA@title{#1}%
}

% MLA header information (new)
\newcommand\firstname[1]{%
  \def\MLA@firstname{#1}%
}
\newcommand\lastname[1]{%
  \def\MLA@lastname{#1}%
  \markright{\hfill\textup{\MLA@lastname}\space}
}
\newcommand\instructor[1]{%
  \def\MLA@instructor{#1}%
}
\newcommand\course[1]{%
  \def\MLA@course{#1}%
}

% Make MLA-compliant title
\renewcommand\maketitle{%
  \noindent\MLA@firstname\space\MLA@lastname

  \noindent\MLA@instructor

  \noindent\MLA@course

  \noindent\MLA@date

  \begin{center}
    \MLA@title
  \end{center}

  \indent%
}


%% Page settings %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Set paper geometry (A4, vertical 1 in, horizontal 3/4 in margin)
\geometry{
  a4paper,
  tmargin=1in,
  bmargin=1in,
  lmargin=0.75in,
  rmargin=0.75in
}

% Set font to Times New Roman for alphabets, Batang for hangul
\setmainfont{Noto Serif}
\setmainhangulfont{Noto Serif CJK KR}

% Use double spaced
\doublespacing{}

% Paragraph indentation must be a half inch
\setlength\parindent{0.5in}

% Default date format
\DTMnewdatestyle{mla}{
  \renewcommand*{\DTMdisplaydate}[4]{%
    ##3 \DTMenglishmonthname{##2} ##1%
  }
  \renewcommand*{\DTMDisplaydate}{%
    \DTMdisplaydate%
  }
}
\DTMsetdatestyle{mla}

% Change bibliography header
\defbibheading{bibliography}{
  \clearpage
  \begin{center}
    Works cited
  \end{center}
}

% Customize headings
\pagestyle{myheadings}
\setlength\topmargin{-0.5in}


%% Before and after document handlers %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Anything required before the document
\AtBeginDocument{
  \maketitle
}

% Anything required after the document
\AtEndDocument{
  \printbibliography
}
