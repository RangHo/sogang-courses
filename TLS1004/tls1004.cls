%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% MLA-compliant Article LaTeX Document Class
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

\ProvidesClass{tls1004}[2024/04/12 v0.1.0 MLA-compliant article class for LaTeX for TLS1004 class]
\NeedsTeXFormat{LaTeX2e}
\LoadClass[12pt]{article}


%% Imported packages %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% American English style
\usepackage[american]{babel}

% Paper geometry settings
\usepackage[a4paper]{geometry}

% OpenType font handler (requires XeTeX or LuaTeX engine)
\usepackage{fontspec}

% Set document-wide spacing
\usepackage{setspace}

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
\newcommand\name[1]{%
  \def\MLA@name{#1}%
}
\newcommand\instructor[1]{%
  \def\MLA@instructor{#1}%
}
\newcommand\course[1]{%
  \def\MLA@course{#1}%
}

% Make MLA-compliant title
\renewcommand\maketitle{%
  {\noindent\MLA@name}

  {\noindent\MLA@course}

  {\noindent\MLA@instructor}

  {\noindent\MLA@date}

  {\centering\MLA@title\par}
}


%% Page settings %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Set paper geometry (margin should be 1 inch all around)
\geometry{margin = 1in}

% Set font to Times New Roman
\setmainfont{Times New Roman}

% Mimic Microsoft Word double-spacing
\setstretch{2.05}

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
\pagenumbering{gobble}
\setlength\topmargin{-0.5in}


%% Before and after document handlers %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Anything required before the document
\AtBeginDocument{%
  \maketitle
}

% Anything required after the document
\AtEndDocument{
  \printbibliography
}
